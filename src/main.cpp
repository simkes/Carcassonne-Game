#include "client.h"
#include "server.h"
#include <SFML/System/Thread.hpp>
#include <iostream>
#include <chrono>
#include <thread>

void init_textures_and_font() {
    carcassonne_game::getTextures().load(game_view::textures::ID::BACKGROUND, "background.jpg");
    carcassonne_game::getTextures().load(game_view::textures::ID::CARDS1, "cardsTextures1-16small.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::CARDS2, "cardsTextures17-21small.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::UNIT_YELLOW, "meeplesTextures/yellowMeeple.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::UNIT_RED, "meeplesTextures/redMeeple.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::UNIT_GREEN, "meeplesTextures/greenMeeple.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::UNIT_BLUE, "meeplesTextures/blueMeeple.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::UNIT_BLACK, "meeplesTextures/blackMeeple.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::TITLE, "carcasonne_title.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::SCORE, "score.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::BACKGROUND_TILE, "background_tile.png");
    carcassonne_game::getFont().loadFromFile("CyrilicOld.TTF");
}

int main() {
    init_textures_and_font();

    carcassonne_game::game_client::Client client;
    client.is_host(); // ask client to be a host/to connect
    unsigned short port =
        client.get_mRender().get_menu().ask_port(); // ask port
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    std::cout << ip << '\n';// default IP  = sf::IpAddress::LocalHost
    if(client.is_host()) {// con-r from port
        sf::Thread hosted_server([&]() {
            carcassonne_game::game_server::ServerGame newGame(port);
            newGame.run();
        });
        try {
            hosted_server.launch();
        } catch (std::exception &exc) {
            std::cout << exc.what();
            hosted_server.terminate();
            return 1;
        }
        sf::TcpSocket host;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        client.hostSocket.connect(ip, port, sf::seconds(5.f));
        sf::Socket::Status status = client.connect(ip, port, sf::seconds(5.f));
        client.run();
        hosted_server.terminate();
    } else {
        sf::IpAddress ip(client.get_mRender().get_menu().ask_IP()); // ask IP
        sf::Socket::Status status = client.connect(ip, port, sf::seconds(5.f));
        if (status == sf::Socket::Done) {
            client.run();
        } // else retry
    }


    //if(client.connect(ip,port, sf::seconds(5.f)) != sf::TcpSocket::Done) {
        std::cout << "Failed to connect\n";
    //}

}