#include "game_cardDeck.h"

inline std::mt19937 rng ((std::uint32_t) std::chrono::steady_clock::now().time_since_epoch().count());

namespace carcassonne_game {

void CardDeck::init() {
    for (int i = 1; i < 15; i++) { // changed from 20 to 15
        std::string filename = "cardsdata/" + std::to_string(i) + ".txt";
        if (i < 3) {
            for (int j = 0; j < 2; j++) { // from 9 to 2
                mDeck.emplace_back(Card(filename, i - 1));
            }
        } else { // from 4 to 1
                mDeck.emplace_back(Card(filename, i - 1));
        }
    }

std::shuffle(mDeck.begin(), mDeck.end(), rng);
}

bool CardDeck::empty() {
    return mDeck.empty();
}

Card CardDeck::get_card() {
    Card newCard = mDeck.back();
    mDeck.pop_back();
    return newCard;
}

} // carcassonne_game