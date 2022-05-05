#include "game_board.h"

namespace game_model {

bool Board::canAddCard(sf::Vector2i pos, Card &card) {
    pos.x = pos.x / (CARD_DIMENSION-1) * (CARD_DIMENSION - 1);
    pos.y = pos.y / (CARD_DIMENSION-1) * (CARD_DIMENSION - 1);
    if (mTiles[sf::Vector2i{pos.x + CARD_DIMENSION / 2, pos.y + CARD_DIMENSION / 2}].card != nullptr) {
        return false;
    }
    if (pos.x % (CARD_DIMENSION - 1) != 0 ||
        pos.y % (CARD_DIMENSION - 1) != 0) {
        return false;
    }
    // TODO: debug, rewrite simpler
    for (int dy : {0, CARD_DIMENSION - 1}) {
        for (int dx = 0; dx < CARD_DIMENSION; dx++) {
            auto board_tile = mTiles[sf::Vector2i{pos.x + dx , pos.y + dy}];
            auto card_tile = card.getTile(dx, dy);
            if (board_tile.card == nullptr || board_tile.type == card_tile.type) {
                continue;
            } else {
                return false;
            }
        }
    }
    for (auto dx : {0, CARD_DIMENSION - 1}) {
        for (int dy = 0; dy < CARD_DIMENSION; dy++) {
            auto board_tile = mTiles[sf::Vector2i{pos.x + dx , pos.y + dy}];
            auto card_tile = card.getTile(dx, dy);
            if (board_tile.card == nullptr || board_tile.type == card_tile.type) {
                continue;
            } else {
                return false;
            }
        }
    }
    return true;
}

const std::vector<sf::Vector2i> cardBounds{ {CARD_DIMENSION - 1,0}, {0, CARD_DIMENSION - 1},
                                           {-CARD_DIMENSION + 1,0}, {0, -CARD_DIMENSION + 1}}; //TODO: rename

const std::vector<std::vector<Tile>> &Board::addCard(sf::Vector2i pos,
                                                      Card &card) {
    pos.x = pos.x / (CARD_DIMENSION-1) * (CARD_DIMENSION - 1);
    pos.y = pos.y / (CARD_DIMENSION-1) * (CARD_DIMENSION - 1);

    for (int dx = 0; dx < CARD_DIMENSION; dx++) {
        for (int dy = 0; dy < CARD_DIMENSION; dy++) {
            //if (mTiles[{pos.x + dx, pos.y + dy}] == nullptr) { // TODO: handle tiles belonging to 2 cards
                card.getTile(dx,dy).position = {pos.x+dx, pos.y+dy};
                //card.mSprite.setOrigin(game_view::transform_coordinates(card.getTile(2, 2).position));
                mTiles[{pos.x + dx, pos.y + dy}] = card.getTile(dx, dy);
                mTypeMap[card.getTile(dx, dy).type].push_back(card.getTile(dx, dy));
           // }
        }
    }

    return card.getTiles();
}

}  // namespace game_model
