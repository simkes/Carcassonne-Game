#ifndef INTERACTION_H_
#define INTERACTION_H_

#include "game_view.h"
#include "game_board.h"
#include "game_card.h"

namespace interaction {

enum class State { CARDPLACEMENT, UNITPLACEMENT, DEFAULT };

struct defaultInteraction{
    game_view::BoardView mainView;
    void handleEvent(sf::Event &event);

}; // may be better to name baseInteraction or smt

struct cardPlacementInteraction: public defaultInteraction{

    //cardPlacementInteraction(game_model::Board &board, game_model::Card &card): Board(board), currentCard(card){}
    void handleEvent(sf::Event &event);

private:
    const game_model::Board &Board;
    game_model::Card &currentCard;
};

struct unitPlacementInteraction: public defaultInteraction{

    void handleEvent(sf::Event &event);
    //cardPlacementInteraction(game_model::Board &board, game_model::Card &card): Board(board), currentCard(card){}

private:
    const game_model::Board &Board;
    game_model::Card &currentCard;
    game_model::Player &currentPlayer;
};

} // namespace interaction

#endif // INTERACTION_H_