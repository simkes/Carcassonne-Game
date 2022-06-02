#include "game_board.h"

namespace game_model {

bool Board::canAddCard(sf::Vector2i pos, Card &card) {

    pos = game_view::to_board_tiles(pos);
    pos.x = (pos.x / (CARD_DIMENSION-1)) * (CARD_DIMENSION - 1);
    pos.y = (pos.y / (CARD_DIMENSION-1)) * (CARD_DIMENSION - 1);
    if (mTiles[sf::Vector2i{pos.x + CARD_DIMENSION / 2, pos.y + CARD_DIMENSION / 2}].card != nullptr) {
        return false;
    }
    if (pos.x % (CARD_DIMENSION - 1) != 0 ||
        pos.y % (CARD_DIMENSION - 1) != 0) {
        return false;
    }
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

const std::vector<std::vector<Tile>> &Board::addCard(sf::Vector2i pos,
                                                      Card &card) {
    card.mPosition = {pos.x, pos.y};

    pos = game_view::to_board_tiles(pos);
    pos.x = (pos.x / (CARD_DIMENSION-1)) * (CARD_DIMENSION - 1);
    pos.y = (pos.y / (CARD_DIMENSION-1)) * (CARD_DIMENSION - 1);
    for (int dx = 0; dx < CARD_DIMENSION; dx++) {
        for (int dy = 0; dy < CARD_DIMENSION; dy++) {
            card.getTile(dx, dy).position = {pos.x + dx, pos.y + dy};
            mTiles[{pos.x + dx, pos.y + dy}] = card.getTile(dx, dy);
            mTypeMap[card.getTile(dx, dy).type].push_back(mTiles[{pos.x + dx, pos.y + dy}]);
        }
    }

    return card.getTiles();
}

}  // namespace game_model
