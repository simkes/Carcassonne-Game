#ifndef GAME_TILE_H
#define GAME_TILE_H

#include <SFML/System/Vector2.hpp>
#include "game_common.h"
#include "game_unit.h"

namespace game_model {

struct Tile {
    Type type = Type::NOTHING;
    sf::Vector2i position;
    Unit *unit = nullptr;
    std::pair<int, int> cardIDs;
    int belongingCastles = 0;  //?
    // TODO: constructor
};

}  // namespace game_model

#endif  // GAME_TILE_H
