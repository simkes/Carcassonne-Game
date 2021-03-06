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
const PacketType UPDATE_CARD = 6;
const PacketType UPDATE_UNIT = 7;
const PacketType UPDATE = 8;
const PacketType MESSAGE = 9;
const PacketType GAME_OVER = 10;
const PacketType GAME_START = 11;
const PacketType PAUSE = 12;
const PacketType CHAT_RECEIVER = 13;
const PacketType CHAT_SENDER = 14;
const PacketType WRONG_PLAYER = 15;

} // namespace carcassonne_game

#endif  // SERVER_COMMON_H