#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include "game_card.h"

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
    bool canAddCard(sf::Vector2i pos, Card &card);

    const std::vector<std::vector<Tile>> &addCard(sf::Vector2i pos, Card &card);

    std::map<sf::Vector2i, Tile, Comp> &getTiles() {
        return mTiles;
    }

    sf::Vector2i getEmptyPosition(sf::Vector2i position);

    std::map<Type, std::vector<Tile>> &getTypeMap(){
        return mTypeMap;
    }

private:
    // TODO: wrap in unique ?
    std::map<sf::Vector2i, Tile, Comp> mTiles;
    std::map<Type, std::vector<Tile>> mTypeMap;
    std::set<sf::Vector2i, Comp> emptyPositions;
    size_t castleCount = 0;
};

}  // namespace game_model


#endif  // GAME_BOARD_H_
