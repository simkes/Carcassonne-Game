#ifndef GAME_H_
#define GAME_H_

#include "game_board.h"
#include "game_player.h"
#include "interaction.h"
#include "game_view.h"
#include "game_render.h"
#include "game_cardDeck.h"
#include "visitors_road.h"
#include "visitors_castle.h"
#include "visitors_monastery.h"
#include "visitors_field.h"

namespace carcassonne_game{

using namespace game_model;
using namespace interaction;
using namespace game_view;

class Game {
public:
    explicit Game(std::vector<std::pair<sf::String, game_model::Color>> players, GameRender *gameRenderPtr);
    void run();

    State get_curState(){
        return currentState;
    }

    Card *currentCardPtr = nullptr;
private:
    bool gameOver = false;

    Board mBoard;
    CardDeck mCardDeck;
    std::vector <Card> placedCards;

    std::vector <Player> mPlayers;
    std::size_t currentPlayerIndex = 0;
    std::size_t numberOfPlayers;
    Player *currentPlayerPtr = nullptr;

    std::vector<std::unique_ptr<visitors::AbstractVisitor>> mVisitors;

    State currentState;
    bool endOfState = false;
    std::map<State, std::unique_ptr<defaultInteraction>> mInteraction;

    GameRender *mGameRenderPtr;

    void init_players(std::vector<std::pair<sf::String, game_model::Color>> &players);
    void init_visitors();
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