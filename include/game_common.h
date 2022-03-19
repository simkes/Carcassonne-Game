#ifndef GAME_COMMON_H_
#define GAME_COMMON_H_

#include <vector>
#include <map>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <string>
#include <memory>

namespace game_model {

const int CARD_DIMENSION = 5;

enum class Type {NOTHING, CASTLE, FIELD, ROAD, MONASTERY, JUNCTION, CASTLEWITHSHIELD};
inline std::vector <Type> typesVector {Type::NOTHING, Type::CASTLE, Type::FIELD, Type::ROAD, Type::MONASTERY, Type::JUNCTION, Type::CASTLEWITHSHIELD};
                                //      0           1           2           3               4               5                   6

enum Color { RED, YELLOW, GREEN, BLUE, BLACK };
inline std::vector <Color> colorsVector{RED, YELLOW, GREEN, BLUE, BLACK};

const int NUMBER_OF_UNITS = 5;

struct Tile;
struct Unit;
struct Card;
struct Player;
struct Board;

}  // namespace game_model

#endif  // GAME_COMMON_H_
