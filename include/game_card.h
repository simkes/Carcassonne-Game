#ifndef GAME_CARD_H_
#define GAME_CARD_H_

#include <array>
#include "game_common.h"
#include "game_model.h"
#include "view_util.h"

namespace game_model {

struct Card {
    Card(const std::string &filename, int texture_id){
        textureId = texture_id;
        std::ifstream ss(filename);
        for (int i = 0; i < CARD_DIMENSION; i++){
            for (int j = 0; j < CARD_DIMENSION; j++){
                int temp;
                ss >> temp;
                mTiles[CARD_DIMENSION - i - 1][j](typesVector[temp]);
            }
        }
    }

    void rotateLeft();   // counterclockwise
    void rotateRight();  // clockwise

    int id;
    int rotation = 0;  // can be 0, 1, 2, 3, where the rotation angle is:
                   // (pi/2)*rotation counterClockWise
    int textureId;
    Tile *getTile(int x, int y) const;
    const std::array<std::array<Tile *, CARD_DIMENSION>, CARD_DIMENSION>
        *getTiles() const;
    std::array<std::array<Tile *, CARD_DIMENSION>, CARD_DIMENSION> mTiles;
};

}  // namespace game_model

#endif  // GAME_CARD_H_
