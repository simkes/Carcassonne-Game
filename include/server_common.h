#ifndef SERVER_COMMON_H
#define SERVER_COMMON_H

#include "SFML/System.hpp"

namespace carcassonne_game {
typedef sf::Uint8 PacketType;
const PacketType INITIAL = 0;
const PacketType ERROR = 1;
const PacketType WAIT_START = 2;

} // namespace carcassonne_game

#endif  // SERVER_COMMON_H
