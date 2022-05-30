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
    UnitView mUnitView;
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
    sf::Vector2f invitationPos = {10,65};
    sf::Text errorMessage; //TODO

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

    void set_errorMessage(const std::string& msg) {
        errorMessage.setString(msg);
    }

    std::pair<sf::String, int> menu_init(const std::vector<int>& available_colors) {
        std::pair<sf::String, int> ans = mMenu.ask_name_color(available_colors);
        mUnitView.set_col_and_pos(ans.second, {invitationPos.x , invitationPos.y + 110});
        return ans;
    }

    void render(carcassonne_game::State state);

    friend interaction::defaultInteraction;
    friend interaction::cardPlacementInteraction;
    friend interaction::unitPlacementInteraction;
};

} // game_view

#endif // GAME_RENDER_H_