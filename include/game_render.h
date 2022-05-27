#ifndef GAME_RENDER_H_
#define GAME_RENDER_H_

#include "game_common.h"
#include "game_menu.h"

namespace interaction {
struct defaultInteraction; // declaration
struct cardPlacementInteraction;
struct unitPlacementInteraction;
}

namespace game_view{

class GameRender {
private:
    sf::RenderWindow mWindow;
    BoardView mBoardView;
    CurrentCardView mCurCardView;
    sf::String mCurPlayer;

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
    Menu& get_menu() {
        return mMenu;
    }
    CurrentCardView& get_curCardView(){
        return mCurCardView;
    }
    BoardView &get_boardView() {
        return mBoardView;
    }

    void set_curPlayer(const std::string& name) {
        mCurPlayer = name;
    }

    void render(bool card);
 //   std::vector<std::pair<sf::String, game_model::Color>> execute_menu();
 //   void set_boardView(game_model::Board *board);

    friend interaction::defaultInteraction;
    friend interaction::cardPlacementInteraction;
    friend interaction::unitPlacementInteraction;
};

} // game_view

#endif // GAME_RENDER_H_