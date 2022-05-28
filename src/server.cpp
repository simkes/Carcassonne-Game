#include "server.h"
#include <iostream>

namespace carcassonne_game::game_server {

void Server::startGame(std::vector<Player> players) {
    for (auto &player : players) {
        int index = player.get_index();
        sf::Packet packet;
        packet << GAME_START << index << player.name << player.color;
        // handle errors
        indSocket[index]->send(packet);
    }
}

sf::Vector2i Server::getCardPlacement(size_t index) {
    sf::Packet packet;
    // handle errors
    // how to check if received correct packet, naive solution is set types to packets as first its bytes
    indSocket[index]->receive(packet);
    PacketType type;
    packet >> type;
    if (type == PLACE_CARD) {
        int x, y;
        packet >> x >> y;
        return {x, y};
    } else {
        sendError("Wrong packet received", index);
    }
    return {-1, -1};
}

void Server::sendError(const std::string &error_msg, size_t index) {
    sf::Packet packet;
    packet << ERROR << error_msg;
    indSocket[index]->send(packet);
}

std::optional<sf::Vector2i> Server::getUnitPlacement(size_t index) {
    sf::Packet packet;
    // handle errors

    indSocket[index]->receive(packet);
    PacketType type;
    packet >> type;
    if (type == PLACE_UNIT) {
        bool isPlaced;
        packet >> isPlaced;
        if (isPlaced) {
            sf::Vector2i pos;
            packet >> pos.x >> pos.y;
            return pos;
        }
        return std::nullopt;
    }
}

void Server::turnDone(size_t index, Card card) {
    for (auto &obj : indSocket) {
        sf::Packet packet;
        packet <<  UPDATE << indPlayer[index].name << card.textureId << card.mPosition.x << card.mPosition.y << card.rotation;
        // handle errors
        obj.second->send(packet);
    }
}

void Server::newTurn(size_t index, Card card) {
    for (auto &obj : indSocket) {
        sf::Packet packet;
        packet << NEW_TURN  << indPlayer[index].name << card.textureId;
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
    int cur_index = 0;
    std::vector<Player> players;
    sf::Packet from_host;
    std::map<int, std::pair<std::string, int>> indConnected;
    do {
        // disconnects
//        for (auto obj : indSocket) {
//            if (!obj.second->getRemotePort()) {
//                lobby.erase(indConnected[obj.first]);
//                obj.second = nullptr;
//            }
//
        if (mListener.accept(*mSockets[cur_index]) == sf::Socket::Done) {
            mSockets[cur_index]->setBlocking(true);
            std::cout << "connected\n";
            sf::Packet packet;
            packet << INITIAL << availableCol;
            for (int i = 0; i < colorsVector.size(); i++) {
                if (!colors[i]) {
                    packet << i;
                }
            }
            mSockets[cur_index]->send(packet);
            packet = sf::Packet();
            if (mSockets[cur_index]->receive(packet) == sf::Socket::Done) {
                PacketType type;
                packet >> type;
                if (type == INITIAL) {
                    std::string name;
                    int color;
                    packet >> name >> color;
                    colors[color] = 1;
                    availableCol--;
                    lobby.insert({name, color});
                    indSocket[cur_index] = mSockets[cur_index++];
                }
            }
            for (auto obj : mSockets) {
                if (obj->getRemotePort()) {
                    sf::Packet packet;
                    packet <<  WAIT_START << static_cast<int>(lobby.size());
                    for (auto pl : lobby) {
                        packet << pl.first;
                    }
                    obj->send(packet);
                }
            }
            mSockets[cur_index - 1]->setBlocking(false);
        }
    } while (mSockets[0]->receive(from_host) != sf::Socket::Done);
    for (auto &obj : lobby) {
        players.emplace_back(obj.first, static_cast<Color>(obj.second));
    }
    return players;
}

} // namespace carcassonne_game::game_server
