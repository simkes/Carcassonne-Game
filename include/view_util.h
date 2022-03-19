#ifndef GAME_VIEW_UTIL_H_
#define GAME_VIEW_UTIL_H_

#include <map>
#include <vector>

namespace game_view {

namespace textures {
enum class ID { CARDS1, CARDS2, BACKGROUND, STARTTEXTURE, UNIT_BLACK, UNIT_BLUE, UNIT_GREEN, UNIT_RED, UNIT_YELLOW};

inline std::map<game_model::Color, ID> unit_color {{game_model::Color::RED, ID::UNIT_RED},{game_model::Color::BLACK, ID::UNIT_BLACK},
                                           {game_model::Color::BLUE, ID::UNIT_BLUE},{game_model::Color::GREEN, ID::UNIT_GREEN},
                                           {game_model::Color::YELLOW, ID::UNIT_YELLOW}};

const int CARD_TEXTURE_SIZE = 379;

inline std::vector<std::pair<int,int>> cardCoordinates{{0,0}, {0,1}, {0,2}, {0,3},
                                             {1,0}, {1,2}, {1,3},{2,1},
                                             {2,3}, {3,0}, {3,1},{3,2},
                                             {4,1}, {4,3}, {5,0}, {5,1},
                                             {1,0}, {1,2}, {4,1}, {4,2},
                                             {4,3}};

} // namespace textures

inline sf::Vector2f transform_coordinates (sf::Vector2i vector) {
    // transformation
}

} // namespace game_view

#endif // GAME_VIEW_UTIL_H_
