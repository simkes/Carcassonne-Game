#ifndef GAME_CARD_H_
#define GAME_CARD_H_

#include "game_tile.h"

namespace game_model {

struct Card {
    Card() = default;
    explicit Card(const std::string &filename, int texture_id){
        mTiles.resize(CARD_DIMENSION);
        textureId = texture_id;
        std::ifstream ss(filename);
        for (int i = 0; i < CARD_DIMENSION; i++){
            for (int j = 0; j < CARD_DIMENSION; j++){
                int temp;
                ss >> temp;
                mTiles[CARD_DIMENSION - i - 1].emplace_back(typesVector[temp]);
            }
        }
    }

    void rotateLeft();   // counterclockwise
    void rotateRight();  // clockwise
    void setTiles();

    int id = 0;
    int rotation = 0;  // can be 0, 1, 2, 3, where the rotation angle is:
                   // (pi/2)*rotation counterClockWise
    int textureId;
    [[nodiscard]] Tile *getTile(int x, int y);
    [[nodiscard]] const std::vector<std::vector<Tile>> &getTiles() const;
    std::vector<std::vector<Tile>> mTiles;
};

}  // namespace game_model

#endif  // GAME_CARD_H_
