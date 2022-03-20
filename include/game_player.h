#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include "game_unit.h"

namespace game_model {

struct Player {
    const std::string name;
    const Color color;
    int score = 0;
    const bool human;

    Player(std::string name_, Color color_)
        : name(std::move(name_)), color(color_), human(true) {
        for(int i = 0; i < NUMBER_OF_UNITS; i++){
            units.emplace_back(this);
        }
    }
    Unit *get_unit(){
        if (usedUnits == NUMBER_OF_UNITS){
            return nullptr;
        }
        return &units[usedUnits++];
    }
private:
    int usedUnits = 0;
    std::vector<Unit> units;
};

}  // namespace game_model

#endif  // GAME_PLAYER_H_
