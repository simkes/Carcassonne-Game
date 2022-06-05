#ifndef GAME_CARD_H_
#define GAME_CARD_H_

#include "game_tile.h"
#include "view_util.h"

namespace game_model {

struct Card {
private:
    std::vector<std::vector<Tile>> mTiles;
    int rotation = 0;  // can be 0, 1, 2, 3, where the rotation angle is:
                       // (pi/2)*rotation counterClockWise
    void rotateRight();  // clockwise

public:
    Card() = default;
    explicit Card(const std::string &filename, int texture_id) {
        mTiles.resize(CARD_DIMENSION);
        textureId = texture_id;
        std::ifstream ss(filename);
        for (int i = 0; i < CARD_DIMENSION; i++){
            for (int j = 0; j < CARD_DIMENSION; j++){
                int temp;
                ss >> temp;
                mTiles[j].emplace_back(typesVector[temp]);
            }
        }
    }

    int id = 0;
    sf::Vector2i mPosition;
    int textureId;

    [[nodiscard]] Tile &getTile(int x, int y);
    [[nodiscard]] const std::vector<std::vector<Tile>> &getTiles() const;
    void setTiles();
    void set_rotation(int rotation_);
    int get_rotation() const {
        return rotation;
    }
};

}  // namespace game_model

#endif  // GAME_CARD_H_
