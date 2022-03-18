#ifndef GAME_H_
#define GAME_H_

#include <deque>
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
 explicit Game(std::vector<Player> players);

   // void addState();
    void run();

private:
    Board mBoard;
    std::vector <Player> mPlayers;
    std::deque <Card> cardDeck;
    std::vector <Card> placedCards;
    int currentPlayer = 0;
    std::size_t numberOfPlayers;
    defaultInteraction *interaction;
    State currentState = State::CARDPLACEMENT;

    sf::RenderWindow mWindow;
    BoardView mBoardView;
    static TextureHolder textures;

    void processEvents();
    void update();
    void render();

};

} // carcassonne_game

#endif // GAME_H_