#include "game_render.h"

namespace game_view{

GameRender::GameRender() : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Carcassonne-Game"), mMenu(mWindow) {
    mBackground.setTexture(*getTextures().get_texture(game_view::textures::ID::BACKGROUND));
    mBackground.setPosition(0,0);
}

void GameRender::render() {
    mWindow.clear();
    mWindow.draw(mBackground);
    mBoardView.draw(mWindow,sf::RenderStates::Default); //TODO: RenderStates ??
    mWindow.display();
}

void GameRender::render_with_card(game_model::Card *curCardPtr) {
    mWindow.clear();
    mWindow.draw(mBackground);
    mBoardView.draw(mWindow,sf::RenderStates::Default); //TODO: RenderStates ??
    mWindow.draw(curCardPtr->mSprite);
    mWindow.display();
}

std::vector<std::pair<std::string, game_model::Color>> GameRender::startGame() {
    return mMenu.init_players();
}

void GameRender::set_boardView(game_model::Board *board) {
    mBoardView.setBoard(board);
}

}// game_view