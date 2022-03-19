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

    explicit cardPlacementInteraction(game_view::BoardView &gameBoardView, game_model::Board *gameBoard_, game_model::Card *currentCard_)
        : defaultInteraction(gameBoardView), gameBoard(gameBoard_), currentCard(currentCard_) {}
    void handleEvent(sf::Event &event) override;

private:
    game_model::Board *gameBoard; //but its so strange, because in BoardView we have board, maybe make getter
    game_model::Card *currentCard;
};

struct unitPlacementInteraction: public defaultInteraction{

    explicit unitPlacementInteraction(game_view::BoardView &gameBoardView, game_model::Board *gameBoard_,
                                      game_model::Card *currentCard_, game_model::Player *currentPlayer_)
        : defaultInteraction(gameBoardView), gameBoard(gameBoard_), currentCard(currentCard_), currentPlayer(currentPlayer_) {}
    void handleEvent(sf::Event &event) override;
    //cardPlacementInteraction(game_model::Board &board, game_model::Card &card): Board(board), currentCardPtr(card){}

private:
    game_model::Board *gameBoard;
    game_model::Card *currentCard;
    game_model::Player *currentPlayer;
};

} // namespace interaction

#endif // INTERACTION_H_