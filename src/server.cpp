#include "server.h"

namespace carcassonne_game::game_server {

void Server::startGame(std::vector<Player> players) {
    for (auto &player : players) {
        int index = player.get_index();
        sf::Packet packet;
        packet << index << player.name << player.color;
        // handle errors
        indSocket[index]->send(packet);
    }
}

sf::Vector2i Server::getCardPlacement(size_t index) {
    sf::Packet packet;
    // handle errors
    // how to check if received correct packet, naive solution is set types to packets as first its bytes
    indSocket[index]->receive(packet);
    int x, y;
    packet >> x >> y;
    return {x, y};
}

bool Server::getUnitPlacement(size_t index) {
    sf::Packet packet;
    // handle errors

    indSocket[index]->receive(packet);
    bool isPlaced;
    packet >> isPlaced;
    return isPlaced;
}

void Server::newTurn(size_t index, Card card) {
    for (auto &obj : indSocket) {
        sf::Packet packet;
        packet << static_cast<int>(index) << card.textureId << card.mPosition.x << card.mPosition.y;
        // handle errors
        obj.second->send(packet);
    }
}

void Server::finishGame() {
    for (auto &obj : indSocket) {
        sf::Packet packet;
        // results
        obj.second->send(packet);
        obj.second->disconnect();
    }
}

void Server::sendPause() {
    for (auto &obj : indSocket) {
        sf::Packet packet;
        // state pause?
        obj.second->send(packet);
    }
}

std::vector<Player> Server::waitConnections() {
    int cur_index = 1;
    std::vector<Player> players;
    // wait host, his choice (same as in cycle)
    while (true) { // while host not started game
        sf::TcpSocket client;
        if (mListener.accept(client) == sf::Socket::Done) {
            // send available colors etc
            // receive his choice
            std::string name;
            Color color;
            mSockets.push_back(&client);
            players.emplace_back(name, color);
            indSocket[cur_index++] = &client;
        }
    }
    return players;
}

} // namespace carcassonne_game::game_server
