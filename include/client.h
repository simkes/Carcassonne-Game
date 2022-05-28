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
    std::map<State, std::unique_ptr<defaultInteraction>> mInteraction;

    State currentState = State::DEFAULT;
    bool interactionEnd = false;
    PacketType curType = INITIAL;

    void init_interaction();
    void process_game();
    void render_lobby();
    void init(sf::Packet &packet);
    void wait_start(sf::Packet &packet);
    void new_turn(sf::Packet &packet);
    void update(sf::Packet &packet);
    sf::Socket::Status receive();
public:
    Client() {
        mSocket.setBlocking(false); // non blocking socket
        init_interaction();
    }
    bool is_host() {
        if (host == -1) {
            host = mRender.get_menu().execute_start();
        }
        return host;
    }
    game_view::GameRender& get_mRender(){
        return mRender;
    }
    void run();
    sf::Socket::Status connect(const sf::IpAddress & IP, unsigned short port, sf::Time timeout);
};

}


#endif  // CARCASSONNE_GAME_CLIENT_H
