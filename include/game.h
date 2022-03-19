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
    Game();
    void run();

private:
    Board mBoard;
    std::deque <Card> cardDeck;
    std::vector <Card> placedCards;
    Card currentCard;

    std::vector <Player> mPlayers;
    int currentPlayerIndex = 0;
    Player *currentPlayerPtr = nullptr;
    std::size_t numberOfPlayers;

    State currentState = State::CARDPLACEMENT;
    std::map<State, std::unique_ptr<defaultInteraction>> interaction;

    sf::RenderWindow mWindow;
    BoardView mBoardView;

    void init_players();
    void init_cardDeck();
    void init_interaction();

    void processEvents();
    void update();
    void render();
    void changeState();

};

} // carcassonne_game

#endif // GAME_H_