#ifndef GAME_COMMON_H_
#define GAME_COMMON_H_

namespace game_model {

const int CARD_DIMENSION = 5;

enum class Type {NOTHING, CASTLE, FIELD, ROAD, MONASTERY, JUNCTION, CASTLEWITHSHIELD};
std::vector <Type> typesVector {Type::NOTHING, Type::CASTLE, Type::FIELD, Type::ROAD, Type::MONASTERY, Type::JUNCTION, Type::CASTLEWITHSHIELD};
                                //      0           1           2           3               4               5                   6
}  // namespace game_model

#endif  // GAME_COMMON_H_
