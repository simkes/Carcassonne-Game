#ifndef GAME_CARD_DECK_H_
#define GAME_CARD_DECK_H_

#include <deque>
#include <algorithm>
#include <random>
#include <chrono>
#include "game_card.h"
using namespace game_model;

namespace carcassonne_game{

struct CardDeck{

    CardDeck(){
        init();
    }
    void init();
    bool empty();
    Card get_card();

private:
    std::deque <Card> mDeck;
};

} // carcassonne_game

#endif // GAME_CARD_DECK_H_