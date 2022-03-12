#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include <string>
#include <vector>
#include <memory>
#include "game_unit.h"

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
        for(int i = 0; i < NUMBEROFUNITS; i++){
            units.emplace_back(std::make_unique<Unit>(this));
        }
    }

private:
    std::vector<std::unique_ptr<Unit>> units;
};

}  // namespace game_model

#endif  // GAME_PLAYER_H_
