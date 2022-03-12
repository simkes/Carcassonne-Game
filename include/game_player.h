#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include <string>
#include <vector>
#include "game_model.h"

namespace game_model {

enum Color { RED, YELLOW, GREEN, BLUE, BLACK };

const int NUMBEROFUNITS = 5;

struct Player {
    const std::string name;
    const Color color;
    int score = 0;
    const bool human;

    Player(std::string name_, Color color_)
        : name(std::move(name_)), color(color_), human(true) {
        units.resize(NUMBEROFUNITS);
    }

private:
    std::vector<std::unique_ptr<Unit>> units;
};

}  // namespace game_model

#endif  // GAME_PLAYER_H_
