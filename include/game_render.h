#ifndef GAME_RENDER_H_
#define GAME_RENDER_H_

#include "game_common.h"
#include "game_menu.h"

namespace interaction {
struct defaultInteraction; // declaration
struct cardPlacementInteraction;
struct unitPlacementInteraction;
struct chatInteraction;
}

namespace game_view{

class GameRender {
private:
    sf::RenderWindow mWindow;
    BoardView mBoardView;
    CurrentCardView mCurCardView;
    UnitView mUnitView;
    sf::String mCurPlayer;

    sf::Text mScoreButton;
    sf::Text mChatButton;
    sf::Vector2f chat_score_pos = {200, 140};
    sf::Sprite mBackground1;
    sf::Sprite mBackground2;
    sf::Sprite mTitle;
    sf::Sprite mScoreSprite;
    sf::Text mText;
    sf::Text mScoreText;
    Menu mMenu;

    sf::Text invitation;
    sf::Vector2f invitationPos = {10,65};
    sf::Text errorMessage; //TODO

    sf::String message;
    std::deque <std::pair<sf::String, sf::String>> chatHistory;
    sf::Text chatHistoryText;
    sf::Text currentMessage;
    sf::Text messageInvitation;
    sf::RectangleShape mChatRect;

public:
    GameRender();
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

    void set_scoreText(const std::vector<std::pair<std::string,int>>& players_score);

    void add_message(const std::string &name, const std::string &new_message){
        if(chatHistory.size() == 10){
            chatHistory.pop_front();
        }
        chatHistory.emplace_back(name, new_message);
    }

    std::pair<sf::String, int> menu_init(const std::vector<int>& available_colors) {
        std::pair<sf::String, int> ans = mMenu.ask_name_color(available_colors);
        mUnitView.set_col_and_pos(ans.second, {invitationPos.x , invitationPos.y + 110});
        return ans;
    }

    void render(carcassonne_game::State state, bool chat);

    friend interaction::defaultInteraction;
    friend interaction::cardPlacementInteraction;
    friend interaction::unitPlacementInteraction;
    friend interaction::chatInteraction;
};

} // game_view

#endif // GAME_RENDER_H_