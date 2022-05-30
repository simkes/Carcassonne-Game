#ifndef GAME_VIEW_UTIL_H_
#define GAME_VIEW_UTIL_H_

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

namespace game_view {

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 700;

namespace textures {
enum class ID { CARDS1, CARDS2, BACKGROUND, UNIT_BLACK, UNIT_BLUE, UNIT_GREEN, UNIT_RED, UNIT_YELLOW, TITLE, SCORE, BACKGROUND_TILE};

inline std::map<game_model::Color, ID> unit_color {{game_model::Color::RED, ID::UNIT_RED},{game_model::Color::BLACK, ID::UNIT_BLACK},
                                           {game_model::Color::BLUE, ID::UNIT_BLUE},{game_model::Color::GREEN, ID::UNIT_GREEN},
                                           {game_model::Color::YELLOW, ID::UNIT_YELLOW}};

const int CARD_TEXTURE_SIZE = 150;
const int UNIT_TEXTURE_SIZE = 70;

inline std::vector<std::pair<int,int>> cardCoordinates{{0,0}, {0,1}, {0,2}, {0,3},
                                             {1,0}, {1,2}, {1,3},{2,1},
                                             {2,3}, {3,0}, {3,1},{3,2},
                                             {4,1}, {4,3}, {5,0}, {5,1},
                                             {1,0}, {1,2}, {4,2}};

} // namespace textures

inline sf::Vector2f transform_coordinates (sf::Vector2i vector) {
    return sf::Vector2f({static_cast<float>(vector.x - 2) * 30 + 74, static_cast<float>(vector.y - 2) * 30 + 74}); // may be some const var-s
}

inline sf::Vector2i to_tiles_coords (sf::Vector2f vector) {
    return sf::Vector2i({static_cast<int>(vector.x / 30), static_cast<int>(vector.y / 30)});
}

inline sf::Vector2f align_card_coords (sf::Vector2f vector) {
    return {static_cast<float>(static_cast<int>(vector.x / game_view::textures::CARD_TEXTURE_SIZE) * game_view::textures::CARD_TEXTURE_SIZE + 74),
           static_cast<float>(static_cast<int>(vector.y / game_view::textures::CARD_TEXTURE_SIZE) * game_view::textures::CARD_TEXTURE_SIZE + 74)};
}
} // namespace game_view

#endif // GAME_VIEW_UTIL_H_
