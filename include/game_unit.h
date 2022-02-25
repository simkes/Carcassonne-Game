#ifndef GAME_UNIT_H
#define GAME_UNIT_H

#include "game_player.h"
#include "game_tile.h"

namespace game_model {

struct Unit {
    explicit Unit(Player *owner_) : owner(owner_) {
    }

private:
    Tile *tile = nullptr;
    const Player *owner = nullptr;
};

}  // namespace game_model

#endif  // GAME_UNIT_H
