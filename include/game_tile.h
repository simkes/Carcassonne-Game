#ifndef GAME_TILE_H
#define GAME_TILE_H

#include "game_common.h"

namespace game_model {

struct Tile {
    explicit Tile(Type type_) : type(type_) {};
    Tile() = default;

    Tile& get() {
        return *this;
    }

    Type type;
    sf::Vector2i position;
    Unit *unit = nullptr;
    std::pair<int, int> cardIDs;
    Card *card = nullptr;
    int belongingCastles = 0;  //?
    // TODO: constructor
};

}  // namespace game_model

#endif  // GAME_TILE_H
