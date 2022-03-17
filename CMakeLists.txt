cmake_minimum_required(VERSION 3.21)
project(Carcassonne_Game)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_NAME "Carcassonne_Game")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

include_directories(include src ${SFML_INCLUDE_DIRS})

add_executable(${EXECUTABLE_NAME}
        include/game_board.h
        include/game_card.h
        include/game_common.h
        include/game_tile.h
        include/game_player.h
        include/game_model.h
        include/game.h
        include/game_unit.h
        include/interaction.h
        include/game_view.h
        include/view_util.h
        src/game_board.cpp
        src/game_card.cpp
        src/game_view.cpp
        src/game.cpp
        src/main.cpp
        src/interaction.cpp
        )
add_executable(main_debug
        src/main.cpp
        )
target_link_libraries(main_debug sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)