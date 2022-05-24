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
        include/game.h
        include/game_unit.h
        include/interaction.h
        include/game_view.h
        include/view_util.h
        include/game_cardDeck.h
        include/game_render.h
        include/game_menu.h
        include/visitors_abstract.h
        include/visitors_castle.h
        include/visitors_field.h
        include/visitors_monastery.h
        include/visitors_road.h
        include/server.h
        src/game_board.cpp
        src/game_card.cpp
        src/game_view.cpp
        src/game.cpp
        src/main.cpp
        src/interaction.cpp
        src/game_cardDeck.cpp
        src/game_render.cpp
        src/game_menu.cpp
        src/visitors_castle.cpp
        src/visitors_field.cpp
        src/visitors_monastery.cpp
        src/visitors_road.cpp
        src/server.cpp
        src/serverGame.cpp
        include/client.h src/client.cpp include/server_common.h)
add_executable(main_debug
        src/main.cpp
        )
target_link_libraries(main_debug sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)