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
    bool gameOver = false;

    Board mBoard;
    std::deque <Card> cardDeck;
    std::vector <Card> placedCards;
    Card *currentCardPtr = nullptr;

    std::vector <Player> mPlayers;
    std::size_t currentPlayerIndex = 0;
    Player *currentPlayerPtr = nullptr;
    std::size_t numberOfPlayers;

    State currentState;
    bool endOfState = false;
    std::map<State, std::unique_ptr<defaultInteraction>> interaction;

    sf::RenderWindow mWindow;
 //   BoardView mBoardView;
    sf::Sprite background;

    void init_players();
    void init_cardDeck();
    void init_interaction();
    void place_first_card();

    void process_events(sf::Event &event);
    void update();
    void render();
    void change_state();
    void set_currentCard();
    void execute_unitPlacement();

};

} // carcassonne_game

#endif // GAME_H_