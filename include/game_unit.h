#ifndef GAME_UNIT_H_
#define GAME_UNIT_H_

#include "game_tile.h"

namespace game_model {

struct Unit {
    explicit Unit(Player *owner_) : owner(owner_) {
    }
    Tile *tile = nullptr;
    Player *owner = nullptr;
};

}  // namespace game_model

#endif  // GAME_UNIT_H_
