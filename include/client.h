#ifndef CARCASSONNE_GAME_CLIENT_H
#define CARCASSONNE_GAME_CLIENT_H

#include "game.h"
#include "server_common.h"
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>
#include <iostream>

namespace carcassonne_game::game_client {

class Client{
private:
    sf::TcpSocket mSocket;
    sf::TcpSocket mChatSendSocket;
    sf::TcpSocket mChatReceiveSocket;
    sf::Mutex mutex;
    int host = -1;

    bool started = false;
    game_view::GameRender mRender;
    std::map<State, std::unique_ptr<defaultInteraction>> mInteraction;
    chatInteraction mChatInteraction;

    State currentState = State::DEFAULT;
    bool interactionEnd = false;
    bool chat = false;
    bool interactionChatEnd = false;
    PacketType curType = PAUSE;

    void init_interaction();
    void process_game();
    void render_lobby();
    void init(sf::Packet &packet);
    void wait_start(sf::Packet &packet);
    void new_turn(sf::Packet &packet);
    void new_card(sf::Packet &packet);
    void new_unit(sf::Packet &packet);
    void update(sf::Packet &packet);
    [[noreturn]] void receiveMessage();
    sf::Socket::Status receive();
public:
    sf::TcpSocket hostSocket;
    Client() : mChatInteraction(&mRender) {
        //       mSocket.setBlocking(false); // non blocking socket
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