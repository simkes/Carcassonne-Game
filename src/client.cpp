#include "client.h"

namespace carcassonne_game::game_client {

sf::Socket::Status Client::connect(const sf::IpAddress &IP,
                                   unsigned short port, sf::Time timeout) {
    return mSocket.connect(IP, port, timeout);
}

sf::Socket::Status Client::receive() {
    sf::Packet packet;
    sf::Socket::Status status = mSocket.receive(packet);
    PacketType type;
    packet>>type;
    if(type == INITIAL) {
        std::pair <std::string, Color> answer;
        PacketType available_colors;
        packet >> available_colors;
       // answer = mRender.menu().init(available_colors);
        // return mSocket.send(name,color);
    } else if( type == WAIT_START) {
        // ...
    }
    else { // error
        std::string error_msg;
        packet >> error_msg;
        //print msg
    }

}

sf::Socket::Status Client::place_card(PacketType type, sf::Packet packet) {
    return sf::Socket::NotReady;
}
sf::Socket::Status Client::place_unit(PacketType type, sf::Packet packet) {
    return sf::Socket::NotReady;
}
sf::Socket::Status Client::update(sf::Packet packet) {
    PacketType smt;
    packet >> smt ;
    // mRender.update(smt);
}

}
