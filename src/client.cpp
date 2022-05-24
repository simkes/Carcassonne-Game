#include "client.h"

namespace carcassonne_game::game_client {

sf::Socket::Status Client::connect(const sf::IpAddress &IP,
                                   unsigned short port, sf::Time timeout) {
    return mSocket.connect(IP, port, timeout);
}

sf::Socket::Status Client::receive() {
    sf::Packet packet;
    sf::Socket::Status status = mSocket.receive(packet);
    PacketType type; // At the beginning of the packet goes its type (server_common.h)
    packet>>type;
    switch (type) {
        case INITIAL: {
            PacketType n;  // receives n - number of colors available, n available colors indexes
            packet >> n;
            std::vector<int> available_colors(n);
            for (int i = 0; i < n; i++) {
                packet >> available_colors[i];  // index of color ( in game_common: 0 = RED, 1 = YELLOW, 2 = GREEN, 3 = BLUE, 4 = BLACK)
            }
            std::pair<std::string, int> answer =
                mRender.get_menu().ask_name_color(available_colors);
            sf::Packet send_packet;
            send_packet
                << type << answer.first
                << answer.second;  // sends (type) INITIAL (string) name (int) color
            return mSocket.send(send_packet);
        }
        case WAIT_START: {
            PacketType n; // receives n - number of players, n strings - names
            packet >> n;
            std::vector<std::string> players_list(n);
            for(int i = 0; i < n; i++){
                packet >> players_list[i]; // names of players in lobby
            }
            bool game_started = mRender.get_menu().start_game(host, players_list); // if client is host returns true - game started, otherwise returns false,
                                                                               // prints list of players in lobby
            if(game_started) {
                sf::Packet send_packet;
                send_packet << type << game_started;  // sends (type) WAIT_START (int) game_started
                return mSocket.send(send_packet);
            }
            break;
        }
        case ERROR:{ // receives some error message
            std::string error_msg;
            packet >> error_msg;
            //print msg
            break;
        }
        case PLACE_CARD: { // just packet type ?
            return place_card();
        }
        case PLACE_UNIT: { // just packet type ?
            return place_unit();
        }
        case NEW_TURN: { // receives (string) current player name, (int) texture of new current card id
            return new_turn(packet);
        }
        case UPDATE: { // receives texture id of placed card, (int, int) its coordinates (cardX, cardY), (int) rotation
                       // when game starts receives first card (as in game.cpp place_first_card)
                       // (int,int) - of placed unit (unitX, unitY) = (-1,-1) if not placed
                       // (int) color of unit (index as in game_common)
                       // make visitors return vector<Vector2i> position of units returned to players and pass it to packet TODO
                       // it may be size of vector and then n pairs (int,int)
                       // current score?
            return update(packet);
        }
    }
    return status;
}

sf::Socket::Status Client::place_card() {
    return sf::Socket::NotReady;
}

sf::Socket::Status Client::place_unit() {
    return sf::Socket::NotReady;
}
sf::Socket::Status Client::new_turn(sf::Packet packet) {
    std::string cur_player_name;
    int cur_card_texture;
    packet >> cur_player_name >> cur_card_texture;
    mRender.get_curCardView().set_texture(cur_card_texture);
    mRender.set_curPlayer(cur_player_name);
    return sf::Socket::Done; // idk what should return
}

sf::Socket::Status Client::update(sf::Packet packet) {
    int texture_id;
    sf::Vector2i placed_card_coords;
    int rotation;
    packet >> texture_id >> placed_card_coords.x >> placed_card_coords.y >> rotation;
    mRender.get_boardView().add_card(texture_id, transform_coordinates(placed_card_coords), rotation); //TODO: make transform coordinates
                                                                                                       // return tiles (2i) to world (2f)
    sf::Vector2i placed_unit_coords;
    int color;
    packet >>  placed_unit_coords.x >> placed_unit_coords.y >> color;
    if(placed_unit_coords.x != -1) {
        mRender.get_boardView().add_unit(color,placed_unit_coords);
    }
    int n; // number of units to be deleted;
    packet >> n;
    sf::Vector2i deleted_unit_coords;
    for(int i = 0; i < n; i++){
        packet >> deleted_unit_coords.x >> deleted_unit_coords.y;
        mRender.get_boardView().delete_unit(deleted_unit_coords);
    }
    // packet >> some score
    return sf::Socket::Done;
}

}
