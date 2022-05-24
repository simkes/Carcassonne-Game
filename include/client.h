#ifndef CARCASSONNE_GAME_CLIENT_H
#define CARCASSONNE_GAME_CLIENT_H

#include "game.h"
#include "server_common.h"
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>

namespace carcassonne_game::game_client {

class Client{
private:
    sf::TcpSocket mSocket;
    int host = -1;

    game_view::GameRender mRender;

public:
    Client() = default;

    bool is_host() {
        if (host == -1) {
            host = mRender.menu().execute_start();
        }
        return host;
    }
    game_view::GameRender& get_mRender(){
        return mRender;
    }

    sf::Socket::Status connect(const sf::IpAddress & IP, unsigned short port, sf::Time timeout);
    sf::Socket::Status place_card (PacketType type, sf::Packet packet);
    sf::Socket::Status place_unit (PacketType type, sf::Packet packet);
    sf::Socket::Status receive();
    sf::Socket::Status update(sf::Packet packet);
};

}


#endif  // CARCASSONNE_GAME_CLIENT_H
