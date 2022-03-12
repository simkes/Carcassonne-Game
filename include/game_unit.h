#ifndef GAME_UNIT_H_
#define GAME_UNIT_H_

#include "game_model.h"

namespace game_model {

struct Unit {
    explicit Unit(Player *owner_) : owner(owner_) {
    }
    const Tile *tile = nullptr;
    const Player *owner = nullptr;
};

}  // namespace game_model

#endif  // GAME_UNIT_H_
