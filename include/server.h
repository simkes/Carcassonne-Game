#ifndef CARCASSONNE_GAME_SERVER_H
#define CARCASSONNE_GAME_SERVER_H

#include "game.h"
#include "game_common.h"
#include "server_common.h"
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>
#include <iostream>

namespace carcassonne_game {

namespace game_server {

static sf::TcpSocket s0;
static sf::TcpSocket s1;
static sf::TcpSocket s2;
static sf::TcpSocket s3;
static sf::TcpSocket s4;
static sf::TcpSocket s5;

struct Server {

    explicit Server(unsigned int port) {
        mListener.listen(port);
        mListener.setBlocking(false);

        s0.setBlocking(false);
        mSockets[0] = &s1;
        mSelector.add(s0);
        mSockets[1] = &s2;
        mSockets[2] = &s3;
        mSockets[3] = &s4;
        mSockets[4] = &s5;

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

    void cardTurnDone (Card card);
    void unitTurnDone (sf::Vector2i unitPos, int unitCol);
    void update(const std::vector<std::pair<std::string,int>> &players_score, const std::vector<sf::Vector2i> &deleted_units);

    std::vector<Player> waitConnections(std::vector<Player> &players);

    bool check_start();


private:


    sf::SocketSelector mSelector;
    std::vector<sf::TcpSocket> sockets;
    std::vector<sf::TcpSocket *> mSockets = std::vector<sf::TcpSocket *>(5, nullptr);
    sf::TcpListener mListener;
    std::map<Player, int> playerInd;
    std::map<int, Player> indPlayer;
    std::map<size_t, sf::TcpSocket*> indSocket;
    std::vector<int> colors = std::vector<int>(5, 0);
    std::set<std::pair<std::string, int>>lobby;
    int availableCol = 5;
};

struct ServerGame {
    // friend struct Server;

    explicit ServerGame(unsigned short port);
    void run();

    State get_curState() {
        return currentState;
    }

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
    Player *currentPlayerPtr = nullptr;

    std::vector<std::unique_ptr<visitors::AbstractVisitor>> mVisitors;

    State currentState;
    bool endOfState = false;
    void init_players(
        const std::vector<Player> &players);
    void init_visitors();

    void place_first_card();

    void update();
    void change_state();
    void set_currentCard();

};

}  // namespace game_server

} // namespace carcassonne_game


#endif  // CARCASSONNE_GAME_SERVER_H