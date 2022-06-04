#ifndef CARCASSONNE_GAME_SERVER_H
#define CARCASSONNE_GAME_SERVER_H

#include "game.h"
#include "game_common.h"
#include "server_common.h"
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>
#include <iostream>

namespace carcassonne_game::game_server {

struct Server {

    explicit Server(unsigned int port) {
        mListener.listen(port);
        mListener.setBlocking(false);

        host.setBlocking(true);
        for (int i = 0 ; i < 5; i++) {
            mSockets.emplace_back(new sf::TcpSocket());
            mChatSender.emplace_back(new sf::TcpSocket());
            mChatReceiver.emplace_back(new sf::TcpSocket());
            availableSocket.insert(i);
        }

    }

    friend struct ServerGame;

    void startGame(std::vector<Player> players);

    void newTurn(size_t index,
                 Card card
                 /*std::vector<carcassonne_game::State> states*/);

    std::pair<sf::Vector2i, int> getCardPlacement(size_t index);

    sf::Vector2i getUnitPlacement(size_t index);

    void sendPause();

    void finishGame();

    void sendError(const std::string &error_msg, size_t index);

    void cardTurnDone (const Card &card);
    void unitTurnDone (sf::Vector2i unitPos, sf::Vector2i viewPos, int unitCol);
    void update(const std::vector<std::pair<std::string,int>> &players_score, const std::vector<sf::Vector2i> &deleted_units);

    std::vector<Player> waitConnections(std::vector<Player> &players);

    void waitChatConnection(int cur_index);

    void sendChatMessage(std::string message);

    bool check_start();


private:

    sf::TcpSocket host;
    sf::SocketSelector mSelector;
    std::vector<std::unique_ptr<sf::TcpSocket>> mSockets;
    std::vector<std::unique_ptr<sf::TcpSocket>> mChatSender;
    std::vector<std::unique_ptr<sf::TcpSocket>> mChatReceiver;
    // std::vector<std::unique_ptr<sf::Thread>> mChatThread;
    std::map<int, std::string> indAddress;

    sf::SocketSelector mChatSelector;
    std::unique_ptr<sf::Thread> mChat;

    std::map<std::pair<std::string, int>, std::string> playerAddress;
    sf::TcpListener mListener;
    std::map<int, std::pair<std::string, int>> indPlayer;
    std::set<int>availableSocket;
    std::map<size_t, sf::TcpSocket*> indSocket;
    std::vector<int> colors = std::vector<int>(5, 0);
    std::set<std::pair<std::string, int>>lobby;
    int availableCol = 5;
    std::mutex chatMutex;
};

struct ServerGame {
    // friend struct Server;

    explicit ServerGame(unsigned short port);

    void run();

    Card *currentCardPtr = nullptr;

private:
    bool gameOver = false;

    Board mBoard;
    CardDeck mCardDeck;
    std::vector<Card> placedCards;
    Server mServer = Server(0);

    std::vector<Player> mPlayers;
    std::size_t currentPlayerIndex = 0;
    std::size_t numberOfPlayers;

    std::vector<std::unique_ptr<visitors::AbstractVisitor>> mVisitors;

    State currentState;
    void init_players(
        const std::vector<Player> &players);
    void init_visitors();

    void place_first_card();


    void update();
    void change_state();
    void set_currentCard();

};

} // namespace carcassonne_game::game_server


#endif  // CARCASSONNE_GAME_SERVER_H