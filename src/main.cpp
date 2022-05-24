#include "client.h"
#include "server.h"
#include <iostream>

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
    unsigned short port = client.get_mRender().menu().ask_port(); // ask port
    sf::IpAddress ip = sf::IpAddress::LocalHost; // default IP  = sf::IpAddress::LocalHost
    if(client.is_host()) {
        //carcassonne_game::game_server::Server server(port); // con-r from port
        // client connects to server and smt
    } else {
        //sf::IpAddress ip(client.get_mRender().menu().ask_IP()); // ask IP
    }

    if(client.connect(ip,port, sf::seconds(5.f)) != sf::TcpSocket::Done) {
        std::cout << "Failed to connect\n";
    }



   // carcassonne_game::Game newGame(gameRender.run(), &gameRender);
//    try {
//        newGame.run();
//    } catch (const std::exception &exc) {
//        std::cout << exc.what();
//    }
}