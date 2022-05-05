#include "game_render.h"

namespace game_view {

GameRender::GameRender()
    : mWindow    (sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Carcassonne-Game"),
      mMenu      (mWindow), mText("", getFont(), 50), invitation("", getFont(), 40) {
    mBackground1.setTexture(*getTextures().get_texture(game_view::textures::ID::BACKGROUND));
    mBackground1.setPosition(0, 0);

    mTitle.setTexture(*getTextures().get_texture(game_view::textures::ID::TITLE));
    mTitle.setPosition((float)WINDOW_WIDTH/3,5);

    mText.setFillColor(sf::Color::Black);
    mText.setPosition(10,5);
    invitation.setFillColor(sf::Color::Black);
    invitation.setPosition(10,70);
}

void GameRender::render(const sf::String &name) {
    mText.setString(name + "'s Move");
    mWindow.clear();
    mWindow.draw(mBackground1);
    mWindow.draw(mTitle);
    mWindow.draw(mText);
    mWindow.setView(mBoardView.getView());
    mBoardView.draw(mWindow,
                    sf::RenderStates::Default);  // TOD: RenderStates ??
    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}

void GameRender::render_with_card(game_model::Card *curCardPtr, const sf::String &name) {
    mText.setString(name + "'s Move");
    invitation.setString("Place the card");

    mWindow.clear();
    mWindow.draw(mBackground1);
    mWindow.draw(mTitle);
    mWindow.draw(mText);
    mWindow.draw(invitation);
    mWindow.setView(mBoardView.getView());
    mBoardView.draw(mWindow,
                    sf::RenderStates::Default);  // TOD: RenderStates ??
    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(curCardPtr->mSprite);
    mWindow.display();
}

std::vector<std::pair<sf::String, game_model::Color>> GameRender::start_game() {
    return mMenu.start_game();
}

void GameRender::set_boardView(game_model::Board *board) {
    mBoardView.setBoard(board);
    //mWindow.setView(mBoardView.getView());
}

}  // namespace game_view