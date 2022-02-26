#include "game_card.h"

namespace game_model {

Tile *Card::getTile(int x, int y) const {
    return mTiles[y][x];
}

const std::array<std::array<Tile *, CARD_DIMENSION>, CARD_DIMENSION>
    *Card::getTiles() const {
    return &mTiles;
}

void Card::rotateRight() {
    std::array<std::array<Tile *, CARD_DIMENSION>, CARD_DIMENSION> tempArray{};
    for (int j = 0; j < CARD_DIMENSION; j++) {
        for (int i = 0; i < CARD_DIMENSION; i++) {
            tempArray[i][CARD_DIMENSION - j - 1] = mTiles[j][i];
        }
    }
    rotation = (rotation + 3) % 4;
    mTiles = tempArray;  // move is not giving anything because  the
                         // trivially-copyable type
}

void Card::rotateLeft() {
    for (int i = 0; i < 3; i++) {
        rotateRight();
    }
    rotation = (rotation + 1) % 4;
}

}  // namespace game_model