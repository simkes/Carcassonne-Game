#ifndef INTERACTION_H_
#define INTERACTION_H_

#include "game_view.h"
#include "game_board.h"
#include "game_card.h"

namespace interaction {

enum class State { CARDPLACEMENT, UNITPLACEMENT, DEFAULT };

struct defaultInteraction{
    explicit defaultInteraction(game_view::BoardView &gameBoardView) : mainView(gameBoardView) {};
    game_view::BoardView mainView;
    virtual void handleEvent(sf::Event &event);
    //virtual destructor??
    virtual ~defaultInteraction() = default;

}; // may be better to name baseInteraction or smt

struct cardPlacementInteraction: public defaultInteraction{

    explicit cardPlacementInteraction(game_view::BoardView &gameBoardView)
        : defaultInteraction(gameBoardView) {}
    void handleEvent(sf::Event &event) override;

private:
    game_model::Board *Board = nullptr; //but its so strange, because in BoardView we have board, maybe make getter
    const game_model::Card *currentCard = nullptr;
};

struct unitPlacementInteraction: public defaultInteraction{

    explicit unitPlacementInteraction(game_view::BoardView &gameBoardView)
        : defaultInteraction(gameBoardView) {}
    void handleEvent(sf::Event &event) override;
    //cardPlacementInteraction(game_model::Board &board, game_model::Card &card): Board(board), currentCard(card){}

private:
    const game_model::Board *Board = nullptr;
    game_model::Card *currentCard = nullptr;
    game_model::Player *currentPlayer = nullptr;
};

} // namespace interaction

#endif // INTERACTION_H_