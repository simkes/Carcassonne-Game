#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <SFML/System.hpp>
#include <array>
#include <map>
#include <vector>
#include "game_common.h"
#include "game_model.h"

namespace game_model {

struct Comp {
    bool operator()(const sf::Vector2i &lhs, const sf::Vector2i &rhs) const {
        if (lhs.x == rhs.x) {
            return lhs.y < rhs.y;
        }
        return lhs.x < rhs.x;
    }
};

struct Board {
    bool canAddCard(sf::Vector2i pos, const Card &card);

    const std::array<std::array<Tile *, CARD_DIMENSION>, CARD_DIMENSION>
        *addCard(sf::Vector2i pos, const Card &card);

    std::map<sf::Vector2i, Tile *, Comp> &getTiles() {
        return mTiles;
    }

private:
    // TODO: wrap in unique ?
    std::map<sf::Vector2i, Tile *, Comp> mTiles;
    std::map<Type, std::vector<Tile *>> mTypeMap;
    size_t castleCount;
};

}  // namespace game_model


#endif  // GAME_BOARD_H_
