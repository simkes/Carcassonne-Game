cmake_minimum_required(VERSION 3.21)
project(Carcassonne_Game)

set(CMAKE_CXX_STANDARD 17)

include_directories(include src)

add_executable(Carcassonne_Game
        include/game_board.h
        include/game_card.h
        include/game_common.h
        include/game_tile.h
        include/game.h
        include/interaction.h
        include/game_view.h
        include/view_util.h
        src/game_board.cpp
        src/game_card.cpp
        src/game_view.cpp
        src/game.cpp
        src/main.cpp
        )
