#ifndef GAME_H_
#define GAME_H_

#include <queue>
#include "game_board.h"
#include "game_player.h"
#include "interaction.h"
#include "game_view.h"

namespace carcassonne_game{
using namespace game_model;
using namespace interaction;
using namespace game_view;

class Game {
public:
 explicit Game(std::vector<Player> players) : mPlayers(std::move(players)), mWindow(sf::VideoMode(640, 480), "Carcassonne-Game"){
};

   // void addState();
    void run();

private:
    Board mBoard;
    std::vector <Player> mPlayers;
    std::queue <Card> cardDeck;
    std::vector <Card> placedCards;
    int currentPlayer = 0;
    defaultInteraction interaction;
    State nextState;
    sf::RenderWindow mWindow;

    void processEvents();
    void update();
    void render();
};

} // carcassonne_game

#endif // GAME_H_