#ifndef GAME_RENDER_H_
#define GAME_RENDER_H_

#include "game_common.h"
#include "game_menu.h"

namespace game_view{

class GameRender {
private:
    sf::RenderWindow mWindow;
    BoardView mBoardView;
    sf::Sprite mBackground1;
    sf::Sprite mBackground2;
    sf::Sprite mTitle;
    sf::Sprite mScoreSprite;
    sf::Text mText;
    sf::Text mScoreText;
    Menu mMenu;

    std::vector<game_model::Player> *players = nullptr; //for scoreboard
    sf::Text invitation;

    void update_scoreboard();
public:
    GameRender();
    void set_players(std::vector<game_model::Player> *players_) {
        players = players_;
    }
    sf::RenderWindow& window() {
        return mWindow;
    };
    void render(const sf::String &name);
    void render_with_card(game_model::Card* curCardPtr,const sf::String &name);
    std::vector<std::pair<sf::String, game_model::Color>> start_game();
    void set_boardView(game_model::Board *board);
    BoardView &get_boardView() {
        return mBoardView;
    }
};

} // game_view

#endif // GAME_RENDER_H_