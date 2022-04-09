#ifndef GAME_RENDER_H_
#define GAME_RENDER_H_

#include "game_common.h"
#include "game_menu.h"

namespace game_view{

class GameRender {
private:
    sf::RenderWindow mWindow;
    //sf::View mView;
    BoardView mBoardView;
    sf::Sprite mBackground;
    sf::Text mText;
    Menu mMenu;

public:
    GameRender();
    sf::RenderWindow& window() {
        return mWindow;
    };
    void render();
    void render_with_card(game_model::Card* curCardPtr);
    std::vector<std::pair<std::string, game_model::Color>> startGame();
    void set_boardView(game_model::Board *board);
    BoardView &get_boardView() {
        return mBoardView;
    }
};

} // game_view

#endif // GAME_RENDER_H_