#ifndef GAME_CARD_H_
#define GAME_CARD_H_

#include <array>
#include "game_common.h"
#include "game_model.h"
#include "view_util.h"

namespace game_model {

struct Card {
    void rotateLeft();   // counterclockwise
    void rotateRight();  // clockwise

    int id;
    int rotation;  // can be 0, 1, 2, 3, where the rotation angle is:
                   // (pi/2)*rotation counterClockWise
    game_view::textures::ID texture_id;
    Tile *getTile(int x, int y) const;
    const std::array<std::array<Tile *, CARD_DIMENSION>, CARD_DIMENSION>
        *getTiles() const;
    std::array<std::array<Tile *, CARD_DIMENSION>, CARD_DIMENSION> mTiles;
};

}  // namespace game_model

#endif  // GAME_CARD_H_
