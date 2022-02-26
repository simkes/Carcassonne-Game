#include "game_board.h"

namespace game_model {

bool Board::canAddCard(sf::Vector2i pos, const Card &card) {
    if (pos.x % (CARD_DIMENSION - 1) != 0 ||
        pos.y % (CARD_DIMENSION - 1) != 0) {
        return false;
    }
    // TODO: debug, rewrite simpler
    for (int dy : {0, CARD_DIMENSION - 1}) {
        for (int dx = 0; dx < CARD_DIMENSION; dx++) {
            if (mTiles[{pos.x + dx, pos.y + dy}]->type !=
                card.getTile(dx, dy)->type) {
                return false;
            }
        }
    }
    for (auto dx : {0, CARD_DIMENSION - 1}) {
        for (int dy = 0; dx < CARD_DIMENSION; dx++) {
            if (mTiles[sf::Vector2i{pos.x + dx, pos.y + dy}]->type !=
                card.getTile(dx, dy)->type) {
                return false;
            }
        }
    }
    return true;
}

const std::array<std::array<Tile *, 5>, 5> *Board::addCard(sf::Vector2i pos,
                                                     const Card &card) {
    for (int dx = 0; dx < CARD_DIMENSION; dx++) {
        for (int dy = 0; dy < CARD_DIMENSION; dy++) {
            if (mTiles[{pos.x + dx, pos.y + dy}] == nullptr) {
                mTiles.insert({{pos.x + dx, pos.y + dy}, card.getTile(dx, dy)});
            }
        }
    }
    return card.getTiles();
}

}  // namespace game_model
