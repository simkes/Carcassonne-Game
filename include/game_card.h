#ifndef GAME_CARD_H_
#define GAME_CARD_H_

#include "game_tile.h"
#include "game_board.h"
#include <array>

namespace game_model {

struct Card {
    Tile* getTile(int x, int y) const;
    std::array<std::array<Tile*, 5>, 5>* getTiles() const;
    std::array<std::array<Tile*, 5>, 5> mTiles;
};

}

#endif // GAME_CARD_H_
