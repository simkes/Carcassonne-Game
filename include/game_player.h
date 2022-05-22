#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include "game_unit.h"
#include <SFML/Network.hpp>

namespace game_model {

struct Player {
    const sf::String name;
    const Color color;
    int score = 0;
    const bool human;

    Player(const sf::String &name_, Color color_)
        : name(name_), color(color_), human(true) {
        units.resize(NUMBER_OF_UNITS, this);
        /*for(int i = 0; i < NUMBER_OF_UNITS; i++){
            units[i] = this;
        }*/
    }

    Unit *get_unit() {
        for (int i = 0; i < NUMBER_OF_UNITS; i++) {
            if (units[i].tile == nullptr) {
                return &units[i];
            }
        }
        return nullptr;
    }

    [[nodiscard]] int get_index() const {
        return index;
    }

private:
    std::vector<Unit> units;
    int index;
    // sf::TcpSocket socket;
};

}  // namespace game_model

#endif  // GAME_PLAYER_H_
