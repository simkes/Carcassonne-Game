#include "client.h"

namespace carcassonne_game::game_client {

void Client::init_interaction() {
    mInteraction.emplace(State::DEFAULT, std::make_unique<defaultInteraction>(&mRender));
    mInteraction.emplace(State::CARDPLACEMENT, std::make_unique<cardPlacementInteraction>(&mRender));
    mInteraction.emplace(State::UNITPLACEMENT, std::make_unique<unitPlacementInteraction>(&mRender));
}

sf::Socket::Status Client::connect(const sf::IpAddress &IP,
                                   unsigned short port, sf::Time timeout) {
    sf::Socket::Status status =  mSocket.connect(IP, port, timeout);
    mSocket.setBlocking(false);
    return status;
}

void Client::process_game() {
    interaction::result ans;
    sf::Event event{};
    while (mRender.window().pollEvent(event)) {
        ans = mInteraction[currentState]->handleEvent(event,
                                                      interactionEnd);
    }
    mRender.render(currentState);
    if (interactionEnd && currentState != State::DEFAULT) {
        sf::Packet packet;
        packet << curType << ans.tile_coordinates.x << ans.tile_coordinates.y
               << ans.card_rotation;
        mSocket.setBlocking(true);
        while(mSocket.send(packet) != sf::Socket::Done){}
        mSocket.setBlocking(false);
    }
    interactionEnd = false;
}

void Client::render_lobby() {
    bool game_started = mRender.get_menu().lobby();
    if(game_started && !started) {
        started = true;
        sf::Packet send_packet;
        send_packet << curType << game_started;
        hostSocket.setBlocking(true);// sends (type) WAIT_START (int) game_started
         (hostSocket.send(send_packet) == sf::Socket::Done);
            //std::cout << "sent\n";
        hostSocket.setBlocking(false);
    }
}

void Client::run() {
    while(mRender.window().isOpen()){
        receive();
        if(curType == WAIT_START){
            render_lobby();
        } else if (curType == GAME_START || (curType > WAIT_START && curType < GAME_OVER)) {
            process_game();
        }
    }
}

sf::Socket::Status Client::receive() {
    sf::Packet packet;
    sf::Socket::Status status = mSocket.receive(packet);
    if(status == sf::Socket::NotReady) { // no packet to receive
        return status;
    }
    // At the beginning of the packet goes its type (server_common.h)
    packet>>curType;

    switch (curType) {
        case INITIAL: {
            init(packet);
            break;
        }
        case WAIT_START: {
            wait_start(packet);
            break;
        }
        case ERROR:{ // receives some error message
            std::string error_msg;
            packet >> error_msg;
            mRender.set_errorMessage(error_msg);
            break;
        }
        case PLACE_CARD: {
            currentState = State::CARDPLACEMENT; // sends (type), (int,int) coordinates of tile where wants to put card and rotation
            break;
        }
        case PLACE_UNIT: {
            currentState = State::UNITPLACEMENT; // sends (type),  (int,int) coordinates of tile where wants to put unit
            break;
        }
        case NEW_TURN: { // receives (string) current player name, (int) texture of new current card id
            new_turn(packet);
            break;
        }
            //TODO:  make visitors return vector<Vector2i> position of units returned to players and pass it to packet
            //                         it may be size of vector and then n pairs (int,int)
            //                         current score
        case UPDATE_CARD: {
            new_card(packet);
            break;
        }
        case UPDATE_UNIT: {
            new_unit(packet);
            break;
        }
        case UPDATE: {
            update(packet);
            break;
        }
        case GAME_OVER: {
            //TODO: print smt and end
            break;
        }
        case PAUSE: {
            //TODO:
            break;
        }
    }
    return status;
}

void Client::init(sf::Packet &packet) {
    int n;  // receives n - number of colors available, n available colors indexes
    packet >> n;
    std::vector<int> available_colors(n);
    for (int i = 0; i < n; i++) {
        packet >> available_colors[i]; // index of color ( in game_common: 0 = RED, 1 = YELLOW, 2 = GREEN, 3 = BLUE, 4 = BLACK)
    }
    std::pair<std::string, int> answer =
        mRender.menu_init(available_colors);
    sf::Packet send_packet;
    send_packet
        << curType << answer.first
        << answer.second;  // sends (type) INITIAL (string) name (int) color
    while(mSocket.send(send_packet) != sf::Socket::Done) {}
}

void Client::wait_start(sf::Packet &packet) {
    int n; // receives n - number of players, n strings - names
    packet >> n;
    std::vector<std::string> players_list(n);
    for(int i = 0; i < n; i++){
        packet >> players_list[i]; // names of players in lobby
    }
    mRender.get_menu().set_list(players_list);
}

void Client::new_turn(sf::Packet &packet) {
    //std::cout << "get turn\n";
    std::string cur_player_name;
    int cur_card_texture;
    packet  >> cur_card_texture >> cur_player_name;
    mRender.get_curCardView().set_texture(cur_card_texture);
    mRender.set_curPlayer(cur_player_name);
}

void Client::new_card(sf::Packet &packet) {
    int texture_id;
    sf::Vector2i placed_card_coords;
    int rotation;
    //std::cout << "get upd card\n";
    packet >> texture_id >> placed_card_coords.x >> placed_card_coords.y >> rotation;
    //std::cout << placed_card_coords.x << ' ' << placed_card_coords.y << '\n';
    mRender.get_boardView().add_card(texture_id, transform_coordinates(placed_card_coords), rotation);
    currentState = State::DEFAULT;
}

void Client::new_unit(sf::Packet &packet) {
    sf::Vector2i placed_unit_coords;
    int color;
    packet >>  placed_unit_coords.x >> placed_unit_coords.y >> color;
    if (placed_unit_coords.x != -1) {
        mRender.get_boardView().add_unit(color, placed_unit_coords);
    }
    currentState = State::DEFAULT;
}

void Client::update(sf::Packet &packet) {
    int n; // number of players
    packet >> n;
    std::vector<std::pair<std::string,int>> players_score(n);
    for(int i = 0; i < n; i ++) {
        std::string name; int score;
        packet >> name >> score;
        players_score[i] = {name,score};
    }
    mRender.set_scoreText(players_score);
    int m; // number of deleted units
    packet >> m;
    sf::Vector2i deleted_unit_coords;
    for(int i = 0; i < m; i++) {
        packet >> deleted_unit_coords.x >> deleted_unit_coords.y;
        mRender.get_boardView().delete_unit(deleted_unit_coords);
    }
}


}