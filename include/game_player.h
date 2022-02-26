#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>
#include <vector>
#include "game_tile.h"
#include "game_unit.h"

namespace game_model {

enum Color { RED, YELLOW, GREEN, BLUE, BLACK };

const int NUMBEROFUNITS = 5;

struct Unit;

struct Player {
    const std::string name;
    const Color color;
    int score = 0;
    const bool human;

    Player(std::string name_, Color color_)
        : name(std::move(name_)), color(color_), human(true) {
    }  // TODO: fill units with unit * ?

private:
    std::vector<Unit *> units;
};

}  // namespace game_model

#endif  // GAME_PLAYER_H
