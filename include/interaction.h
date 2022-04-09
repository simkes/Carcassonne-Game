#ifndef INTERACTION_H_
#define INTERACTION_H_

#include "game_board.h"
#include "game_card.h"
#include "game_view.h"

namespace interaction {

struct defaultInteraction {
    explicit defaultInteraction(game_model::Board &gameBoard_,
                                game_view::BoardView &mainView_)
        : gameBoard(gameBoard_), mainView(mainView_){};
    virtual void handleEvent(sf::Event &event, bool &endOfState);
    // virtual destructor??
    virtual ~defaultInteraction() = default;

protected:
    game_view::BoardView mainView;
    game_model::Board gameBoard;
};  // may be better to name baseInteraction or smt

struct cardPlacementInteraction : public defaultInteraction {
    explicit cardPlacementInteraction(game_model::Board gameBoard_,
                                      game_view::BoardView &mainView_,
                                      game_model::Card *currentCard_)
        : defaultInteraction(gameBoard_, mainView_), currentCard(currentCard_) {
    }
    void handleEvent(sf::Event &event, bool &endOfState) override;

private:
    // but its so strange, because in BoardView we have board, maybe make getter
    game_model::Card *currentCard;
};

struct unitPlacementInteraction : public defaultInteraction {
    explicit unitPlacementInteraction(game_model::Board gameBoard_,
                                      game_view::BoardView &mainView_,
                                      game_model::Card *currentCard_,
                                      game_model::Player *currentPlayer_)
        : defaultInteraction(gameBoard_, mainView_),
          currentCard(currentCard_),
          currentPlayer(currentPlayer_) {
    }
    void handleEvent(sf::Event &event, bool &endOfState) override;
    // cardPlacementInteraction(game_model::Board &board, game_model::Card
    // &card): Board(board), currentCardPtr(card){}

private:
    game_model::Card *currentCard;
    game_model::Player *currentPlayer;
};

}  // namespace mInteraction

#endif  // INTERACTION_H_