#ifndef CARCASSONNE_GAME_SERVER_H
#define CARCASSONNE_GAME_SERVER_H

#include "game.h"
#include "game_common.h"
#include "server_common.h"
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>

namespace carcassonne_game {

namespace game_server {

struct Server {

    explicit Server(unsigned int port) {
        mListener.listen(port);
        mListener.setBlocking(true);

        mSockets[0] = &s1;
        s1.setBlocking(false);
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

    sf::Vector2i getCardPlacement(size_t index);

    std::optional<sf::Vector2i> getUnitPlacement(size_t index);

    void sendPause();

    void finishGame();

    void sendError(const std::string &error_msg, size_t index);

    void turnDone(size_t index, Card card);

    std::vector<Player> waitConnections();

    // bool send_data(sf::Vector2i pos, size_t card_index);

private:
    sf::TcpSocket s1;
    sf::TcpSocket s2;
    sf::TcpSocket s3;
    sf::TcpSocket s4;
    sf::TcpSocket s5;


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
    // std::map<State, std::unique_ptr<defaultInteraction>> mInteraction;

    // GameRender *mGameRenderPtr;

    void init_players(
        const std::vector<Player> &players);
    void init_visitors();
    // void init_interaction();
    void place_first_card();

    // void process_events(sf::Event &event);
    void update();
    // void render();
    void change_state();
    void set_currentCard();
    void execute_unitPlacement();
};

}  // namespace game_server

} // namespace carcassonne_game


#endif  // CARCASSONNE_GAME_SERVER_H
