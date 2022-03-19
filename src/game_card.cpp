#include "game_card.h"

namespace game_model {

Tile *Card::getTile(int x, int y) {
    return mTiles[y][x].get();
}

const std::vector<std::vector<Tile>> &Card::getTiles() const{
    return mTiles;
}

void Card::rotateRight() {
    std::vector<std::vector<Tile>> tempVector(CARD_DIMENSION,std::vector<Tile>(CARD_DIMENSION));
    for (int j = 0; j < CARD_DIMENSION; j++) {
        for (int i = 0; i < CARD_DIMENSION; i++) {
            tempVector[i][CARD_DIMENSION - j - 1] = mTiles[j][i];
        }
    }
    rotation = (rotation + 3) % 4;
    mTiles = std::move(tempVector);
}

void Card::rotateLeft() {
    for (int i = 0; i < 3; i++) {
        rotateRight();
    }
    rotation = (rotation + 1) % 4;
}

}  // namespace game_model