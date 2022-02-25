#ifndef GAME_CARD_H_
#define GAME_CARD_H_

#include <array>
#include "game_board.h"
#include "game_tile.h"

namespace game_model {

struct Card {
    Tile *getTile(int x, int y) const;
    std::array<std::array<Tile *, 5>, 5> *getTiles() const;
    std::array<std::array<Tile *, 5>, 5> mTiles;
};

}  // namespace game_model

#endif  // GAME_CARD_H_
