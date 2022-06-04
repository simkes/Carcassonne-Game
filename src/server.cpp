#include "server.h"
#include <iostream>
#include <memory>

namespace carcassonne_game::game_server {

void Server::startGame(std::vector<Player> players) {
    for (auto &player : players) {
        int index = player.get_index();
        sf::Packet packet;
        packet << GAME_START << index << player.name << player.color;
        // handle errors
        indSocket[index]->setBlocking(true);
        if (indSocket[index]->send(packet) == sf::Socket::Disconnected) {
            throw std::runtime_error("disconnected");
        }
        indSocket[index]->setBlocking(false);
    }
}

std::pair<sf::Vector2i, int> Server::getCardPlacement(size_t index) {
    sf::Packet packet;
    sf::Packet invite;
    // handle errors
    invite << PLACE_CARD;
    indSocket[index]->setBlocking(true);
    if (indSocket[index]->send(invite) == sf::Socket::Disconnected) {
        throw std::runtime_error("disconnected");
    }
    if (indSocket[index]->receive(packet) == sf::Socket::Disconnected) {
        throw std::runtime_error("disconnected");
    }
    indSocket[index]->setBlocking(false);
    PacketType type;
    packet >> type;
    if (type == PLACE_CARD) {
        int x, y, rotation;
        packet >> x >> y >> rotation;
        return {{x, y},rotation};
    } else {
        sendError("Wrong packet received", index);
    }
    return {{-1, -1},0};
}

sf::Vector2i Server::getUnitPlacement(size_t index) {
    sf::Packet packet;
    sf::Packet invite;
    invite << PLACE_UNIT;
    // handle errors
    indSocket[index]->setBlocking(true);

    if (indSocket[index]->send(invite) == sf::Socket::Disconnected) {
        throw std::runtime_error("disconnected");
    }
    if (indSocket[index]->receive(packet) == sf::Socket::Disconnected) {
        throw std::runtime_error("disconnected");
    }
    indSocket[index]->setBlocking(false);
    PacketType type;
    packet >> type;
    if (type == PLACE_UNIT) {
        sf::Vector2i pos;
        packet >> pos.x >> pos.y;
        return pos;
    }
    else {
        sendError("Wrong packet received", index);
        return {-1, -1};
    }
}

void Server::sendError(const std::string &error_msg, size_t index) {
    sf::Packet packet;
    packet << ERROR << error_msg;
    if (indSocket[index]->send(packet) == sf::Socket::Disconnected) {
        throw std::runtime_error("disconnected");
    }
}

void Server::cardTurnDone(const Card &card) {
    for (auto &obj : indSocket) {
        sf::Packet packet;
        packet << UPDATE_CARD << card.textureId << card.mPosition.x << card.mPosition.y << card.get_rotation();
        // handle errors

        obj.second->setBlocking(true);
        if (obj.second->send(packet) == sf::Socket::Disconnected) {
            throw std::runtime_error("disconnected");
        }
        obj.second->setBlocking(false);
    }
}

void Server::unitTurnDone(sf::Vector2i unitPos,  sf::Vector2i viewPos, int unitCol) {
    for (auto &obj : indSocket) {
        sf::Packet packet;
        packet << UPDATE_UNIT << unitPos.x << unitPos.y << viewPos.x << viewPos.y <<  unitCol;
        // handle errors

        obj.second->setBlocking(true);
        if (obj.second->send(packet) == sf::Socket::Disconnected) {
            throw std::runtime_error("disconnected");
        }
        obj.second->setBlocking(false);
    }
}

void Server::update(const std::vector<std::pair<std::string,int>> &players_score,
                    const std::vector<sf::Vector2i> &deleted_units) {
    int n = (int)players_score.size();
    int m = (int)deleted_units.size();
    for (auto &obj : indSocket) {
        sf::Packet packet;
        packet << UPDATE << n;
        for(const auto &p : players_score) {
            packet << p.first << p.second;
        }
        packet << m;
        for(const auto &p : deleted_units) {
            packet << p.x << p.y;
        }
        obj.second->setBlocking(true);
        if (obj.second->send(packet) == sf::Socket::Disconnected) {
            throw std::runtime_error("disconnected");
        }
        obj.second->setBlocking(false);
    }

}


void Server::newTurn(size_t index, Card card) {
    for (auto &obj : indSocket) {
        sf::Packet packet;
        packet << NEW_TURN << card.textureId << indPlayer[index].first;
        // handle errors
        obj.second->setBlocking(true);
        if (obj.second->send(packet) == sf::Socket::Disconnected) {
            throw std::runtime_error("disconnected");
        }
        obj.second->setBlocking(false);
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
        obj.second->send(packet);
    }
}

void Server::sendChatMessage(std::string message) {
    sf::Packet packet;
    packet >> message;
    for (const auto &obj : mChatSender) {
        if (obj->getRemotePort()) {
            obj->send(packet);
        }
    }
}

bool Server::check_start() {
    std::set<int> deleted;
    for (auto obj : indSocket) {
        if (!obj.second->getRemotePort()) {
            lobby.erase(indPlayer[obj.first]);
            availableSocket.insert(obj.first);
            availableCol++;
            colors[indPlayer[obj.first].second] = 0;
            deleted.insert(obj.first);
        }
    }
    for (auto i : deleted) {
        indPlayer.erase(i);
        indSocket.erase(i);
    }
    for (const auto &obj : mSockets) {
        if (obj->getRemotePort()) {
            sf::Packet packet;
            packet <<  WAIT_START << static_cast<int>(lobby.size());
            for (const auto& pl : lobby) {
                packet << pl.first;
            }
            obj->send(packet);
        }
    }
    if (mSelector.wait(sf::seconds(2.f))) {
        sf::Packet packet;
        host.receive(packet);
        return true;
    } else {
        return false;
    }
}

void Server::waitChatConnection(int cur_index) {
    while (1) {
        mListener.accept(*mChatReceiver[cur_index]);
        sf::Packet packet;
        mChatReceiver[cur_index]->receive(packet);
        PacketType type;
        packet >> type;
        if (type == CHAT_RECEIVER) {
            std::string ip;
            ip = mChatReceiver[cur_index]->getRemoteAddress().toString();
            if (ip == indAddress[cur_index]) {
                sf::Packet to_be_sent;
                to_be_sent << CHAT_RECEIVER;
                mChatReceiver[cur_index]->send(to_be_sent);
                std::unique_lock lock(chatMutex);
                mChatSelector.add(*mChatReceiver[cur_index]);
                break;
            } else {
                sf::Packet to_be_sent;
                to_be_sent << WRONG_PLAYER;
                mChatReceiver[cur_index]->send(to_be_sent);
            }
        }
        mChatReceiver[cur_index]->disconnect();
    }

    while (1) {
        mListener.accept(*mChatSender[cur_index]);
        sf::Packet packet;
        mChatSender[cur_index]->receive(packet);
        PacketType type;
        packet >> type;
        if (type == CHAT_SENDER) {
            std::string ip;
            ip = mChatReceiver[cur_index]->getRemoteAddress().toString();
            if (ip == indAddress[cur_index]) {
                sf::Packet to_be_sent;
                to_be_sent << CHAT_SENDER;
                mChatSender[cur_index]->send(packet);
                break;
            } else {
                sf::Packet to_be_sent;
                to_be_sent << WRONG_PLAYER;
                mChatSender[cur_index]->send(packet);
            }
        }
        mChatSender[cur_index]->disconnect();
    }
}

std::vector<Player> Server::waitConnections(std::vector<Player> &players) {
    while (mListener.accept(host) != sf::Socket::Done) {}
    mChat = std::make_unique<sf::Thread>([this]{
        while (true) {
            std::unique_lock lock(chatMutex);
            if (mChatSelector.wait(sf::seconds(0.5))) {
                for (const auto &socket : mChatReceiver) {
                    if (mChatSelector.isReady(*socket)) {
                        sf::Packet packet;
                        std::string message;
                        socket->receive(packet);
                        packet >> message;
                        sendChatMessage(message);
                    }
                }
            }
        }
    });
    mChat->launch();
    mSelector.add(host);
    sf::Packet from_host;
    std::map<int, std::pair<std::string, int>> indConnected;
    do {
        int cur_index = *availableSocket.begin();
        if (cur_index < 5) {
            if (mListener.accept(*mSockets[cur_index]) == sf::Socket::Done) {
                indAddress[cur_index] = mSockets[cur_index]->getRemoteAddress().toString();
                waitChatConnection(cur_index);
                mSockets[cur_index]->setBlocking(true);
                sf::Packet packet;
                packet << INITIAL << availableCol;
                for (int i = 0; i < colorsVector.size(); i++) {
                    if (!colors[i]) {
                        packet << i;
                    }
                }
                mSockets[cur_index]->send(packet);
                packet.clear();
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
                        playerAddress[{name, color}] = mSockets[cur_index]->getRemoteAddress().toString();
                        indSocket[cur_index] = mSockets[cur_index].get();
                        indPlayer[cur_index] = {name, color};
                    }
                }

                availableSocket.erase(cur_index);
                mSockets[cur_index]->setBlocking(false);
                cur_index = *availableSocket.begin();
            }
        }
    } while (!check_start());
    int iter = 0;
    players.reserve(lobby.size());
    for (const auto& obj : lobby) {
        players.emplace_back(iter, obj.first, static_cast<Color>(obj.second));
        //indPlayer.insert({iter++, players.back()});
    }
    return players;
}

} // namespace carcassonne_game::game_server