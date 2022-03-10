#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <SFML/System/Vector2.hpp>
#include <array>
#include <map>
#include <vector>
#include "game_card.h"
#include "game_common.h"
#include "game_tile.h"

namespace game_model {

struct Board {
    bool canAddCard(sf::Vector2i pos, const Card &card);

    const std::array<std::array<Tile *, CARD_DIMENSION>, CARD_DIMENSION>
        *addCard(sf::Vector2i pos, const Card &card);

    std::map<sf::Vector2i, Tile *> &getTiles() const {
        return mTiles;
    }

private:
    // TODO: wrap in unique ?
    std::map<sf::Vector2i, Tile *> mTiles;
    std::map<Type, std::vector<Tile *>> mTypeMap;
    size_t castleCount;
};

}  // namespace game_model

#endif  // GAME_BOARD_H_
