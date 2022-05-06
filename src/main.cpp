#include "game.h"
#include <iostream>

void init_textures_and_font() {
    carcassonne_game::getTextures().load(game_view::textures::ID::BACKGROUND, "background.jpg");
    carcassonne_game::getTextures().load(game_view::textures::ID::CARDS1, "cardsTextures1-16small.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::CARDS2, "cardsTextures17-21small.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::UNIT_YELLOW, "meeplesTextures/yellowMeeple.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::UNIT_RED, "meeplesTextures/redMeeple.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::UNIT_GREEN, "meeplesTextures/greenMeeple.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::UNIT_BLUE, "meeplesTextures/blueMeeple.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::UNIT_BLACK, "meeplesTextures/blackMeeple.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::TITLE, "carcasonne_title.png");
    carcassonne_game::getTextures().load(game_view::textures::ID::SCORE, "score.png");

    carcassonne_game::getFont().loadFromFile("CyrilicOld.TTF");
}

int main() {
    init_textures_and_font();
    game_view::GameRender gameRender;
    carcassonne_game::Game newGame(gameRender.start_game(), &gameRender);
    try {
        newGame.run();
    } catch (const std::exception &exc) {
        std::cout << exc.what();
    }
}