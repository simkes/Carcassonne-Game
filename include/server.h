#ifndef CARCASSONNE_GAME_SERVER_H
#define CARCASSONNE_GAME_SERVER_H

#include "game.h"
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>

namespace carcassonne_game {

namespace game_server {

struct Server {

    friend struct ServerGame;

    void startGame(std::vector<Player> players);

    void newTurn(size_t index,
                 Card card
                 /*std::vector<carcassonne_game::State> states*/);

    sf::Vector2i getCardPlacement(size_t index);

    bool getUnitPlacement(size_t index);

    void sendPause();

    void finishGame();

    std::vector<Player> waitConnections();

    // bool send_data(sf::Vector2i pos, size_t card_index);

private:
    std::vector<sf::TcpSocket *> mSockets;
    sf::TcpListener mListener;
    std::map<Player, int> playerInd;
    std::map<size_t, sf::TcpSocket*> indSocket;
};

struct ServerGame {
    // friend struct Server;

    explicit ServerGame(std::vector<std::pair<sf::String, game_model::Color>> players);
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
    Server mServer;

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
        std::vector<std::pair<sf::String, game_model::Color>> &players);
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
