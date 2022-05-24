#ifndef SERVER_COMMON_H
#define SERVER_COMMON_H

#include "SFML/System.hpp"
#include "game_common.h"

namespace carcassonne_game {
typedef sf::Uint8 PacketType;

const PacketType INITIAL = 0;
const PacketType ERROR = 1;
const PacketType WAIT_START = 2;
const PacketType PLACE_CARD = 3;
const PacketType PLACE_UNIT = 4;
const PacketType NEW_TURN = 5;
const PacketType UPDATE = 6;

} // namespace carcassonne_game

#endif  // SERVER_COMMON_H
