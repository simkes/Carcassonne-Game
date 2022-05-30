#include "game_render.h"

namespace game_view {

GameRender::GameRender()
    : mWindow    (sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Carcassonne-Game"),
      mMenu      (mWindow), mText("", getFont(), 50), invitation("", getFont(), 40),
      mScoreText("", getFont(), 30) {
    mBackground1.setTexture(*getTextures().get_texture(game_view::textures::ID::BACKGROUND));
    mBackground1.setPosition(0, 0);
    getTextures().get_texture(game_view::textures::ID::BACKGROUND_TILE)->setRepeated(true);
    mBackground2.setTexture(*getTextures().get_texture(game_view::textures::ID::BACKGROUND_TILE));
    mBackground2.setTextureRect({0, 0, 6000, 6000});
    mTitle.setTexture(*getTextures().get_texture(game_view::textures::ID::TITLE));
    mTitle.setPosition((float)WINDOW_WIDTH/3,5);

    sf::Vector2f scorePos = {780,5};
    mScoreSprite.setTexture(*getTextures().get_texture(game_view::textures::ID::SCORE));
    mScoreSprite.setPosition(scorePos);
    mScoreText.setFillColor(sf::Color::Black);
    mScoreText.setPosition(scorePos.x+30,scorePos.y+70);

    mText.setFillColor(sf::Color::Black);
    mText.setPosition(10,5);
    invitation.setFillColor(sf::Color::Red);
    invitation.setPosition(10,70);
}

void GameRender::update_scoreboard() {
    if(!players) { return; }
    sf::String text = "";
    for(const auto &p : (*players)) {
        text += p.name + "      " + std::to_string(p.score) + '\n';
    }
    mScoreText.setString(text);
}


void GameRender::render(carcassonne_game::State state) {
    update_scoreboard();
    mText.setString(mCurPlayer + "'s Move");
    if(state == carcassonne_game::State::CARDPLACEMENT) {
        invitation.setString("Place the card");
    } else if (state == carcassonne_game::State::UNITPLACEMENT) {
        invitation.setString("You can place a unit\n\n Press ENTER to skip");
    }
    mWindow.clear();
    mWindow.draw(mBackground1);
    mWindow.setView(mBoardView.getView());
    mWindow.draw(mBackground2);
    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mScoreSprite);
    mWindow.draw(mScoreText);
    mWindow.draw(mTitle);
    mWindow.draw(mText);
    mWindow.setView(mBoardView.getView());
    mBoardView.draw(mWindow,
                    sf::RenderStates::Default);  // TOD: RenderStates ??
    mWindow.setView(mWindow.getDefaultView());
    if(state != carcassonne_game::State::DEFAULT) {
        mWindow.draw(invitation);
    }
    if (state != carcassonne_game::State::UNITPLACEMENT) {
        mCurCardView.draw(mWindow);
    }
    mWindow.display();
}

//std::vector<std::pair<sf::String, game_model::Color>> GameRender::execute_menu() {
//    return mMenu.run();
//}
//
//void GameRender::set_boardView(game_model::Board *board) {
//    mBoardView.setBoard(board);
//    //mWindow.setView(mBoardView.getView());
//}


}  // namespace game_view