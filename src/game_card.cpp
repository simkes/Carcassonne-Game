#include "game_card.h"

#include <utility>

namespace game_model {

Tile &Card::getTile(int x, int y) {
    return mTiles[x][y].get();
}

const std::vector<std::vector<Tile>> &Card::getTiles() const{
    return mTiles;
}

void Card::rotateRight() {
    std::vector<std::vector<Tile>> tempVector(CARD_DIMENSION,std::vector<Tile>(CARD_DIMENSION));
    for (int j = 0; j < CARD_DIMENSION; j++) {
        for (int i = 0; i < CARD_DIMENSION; i++) {
            tempVector[CARD_DIMENSION - i - 1][j] = mTiles[j][i];
        }
    }
    mTiles = std::move(tempVector);
}

void Card::setTiles() {
    for (int i = 0; i < CARD_DIMENSION; i++){
        for (int j = 0; j < CARD_DIMENSION; j++){
            mTiles[CARD_DIMENSION - i - 1][j].cardIDs = std::make_pair(id, -1);
            mTiles[CARD_DIMENSION - i - 1][j].card = this;
        }
    }
}
void Card::set_rotation(int rotation_) {
    int diff = (rotation_ + 4 - rotation) % 4;
    for(int i = 0; i < diff; i++) {
        rotateRight();
    }
    rotation = rotation_;
}

}  // namespace game_model