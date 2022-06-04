#include "game_render.h"

namespace game_view {

GameRender::GameRender()
    : mWindow    (sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Carcassonne-Game"),
      mMenu      (mWindow), mText("", getFont(), 50), invitation("", getFont(), 35),
      mScoreText("", getFont(), 30), chatHistoryText("", getFont(), 30),
      currentMessage("", getFont(), 30), mScoreButton("Scoreboard", getFont(), 55),
      mChatButton("Chat", getFont(), 55), messageInvitation("Enter a message:", getFont(), 30) {
    mBackground1.setTexture(*getTextures().get_texture(game_view::textures::ID::BACKGROUND));
    mBackground1.setPosition(0, 0);
    getTextures().get_texture(game_view::textures::ID::BACKGROUND_TILE)->setRepeated(true);
    mBackground2.setTexture(*getTextures().get_texture(game_view::textures::ID::BACKGROUND_TILE));
    mBackground2.setTextureRect({0, 0, 6000, 6000});
    mTitle.setTexture(*getTextures().get_texture(game_view::textures::ID::TITLE));
    mTitle.setPosition((float)WINDOW_WIDTH/3,5);

    sf::Vector2f scorePos = {780,60};
    mScoreSprite.setTexture(*getTextures().get_texture(game_view::textures::ID::SCORE));
    mScoreSprite.setPosition(scorePos);
    mScoreText.setFillColor(sf::Color::Black);
    mScoreText.setPosition(scorePos.x+30,scorePos.y+70);

    mText.setFillColor(sf::Color::Black);
    mText.setPosition(10,5);
    invitation.setFillColor(sf::Color::Red);
    invitation.setPosition(invitationPos);

    chatHistoryText.setPosition(212,150);
    chatHistoryText.setFillColor(sf::Color::Black);

    messageInvitation.setPosition(212, 470);
    messageInvitation.setFillColor(sf::Color::Black);
    currentMessage.setPosition(212, 520);
    currentMessage.setFillColor(sf::Color::Black);

    mChatRect.setSize({450, 450});
    mChatRect.setPosition(chat_score_pos);
    mChatRect.setFillColor(sf::Color(255, 218, 185));
    mChatButton.setPosition(810, 5);
    mChatButton.setFillColor(sf::Color::Red);

}

void GameRender::render(carcassonne_game::State state, bool chat) {
    mChatButton.setFillColor(sf::Color::White);
    mText.setString(mCurPlayer + "'s Move");
    if(state == carcassonne_game::State::CARDPLACEMENT) {
        invitation.setString("Place the card");
    } else if (state == carcassonne_game::State::UNITPLACEMENT) {
        invitation.setString("You can place a unit\n Press ENTER to skip");
    }
    if (chat){
        currentMessage.setString(message);
        sf::String chatHistoryString;
        for (const auto &pair : chatHistory) {
            chatHistoryString += pair.first + ": " + pair.second + '\n';
        }
        chatHistoryText.setString(chatHistoryString);
    }
    if (sf::IntRect(810, 5, 55*4, 55).contains(sf::Mouse::getPosition(mWindow))) {
            mChatButton.setFillColor(sf::Color::Red);
    }
    mWindow.clear();
    mWindow.draw(mBackground1);
    mWindow.setView(mBoardView.getView());
    mWindow.draw(mBackground2);
    mWindow.setView(mWindow.getDefaultView());
    mWindow.setView(mBoardView.getView());
    mBoardView.draw(mWindow,
                    sf::RenderStates::Default);
    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mScoreSprite);
    mWindow.draw(mScoreText);
    mWindow.draw(mTitle);
    mWindow.draw(mText);
    mWindow.draw(mChatButton);

    if(state != carcassonne_game::State::DEFAULT) {
        mWindow.draw(invitation);
    }
    if (state != carcassonne_game::State::UNITPLACEMENT) {
        mCurCardView.draw(mWindow);
    }
    if(state == carcassonne_game::State::UNITPLACEMENT) {
        mUnitView.draw(mWindow);
    }
    if (chat) {
        mWindow.draw(mChatRect);
        mWindow.draw(chatHistoryText);
        mWindow.draw(messageInvitation);
        mWindow.draw(currentMessage);
    }
    mWindow.display();
}

void GameRender::set_scoreText(const std::vector<std::pair<std::string, int>>& players_score) {
    sf::String text = "";
    for(const auto &p : players_score) {
        text += p.first + "      " + std::to_string(p.second) + '\n';
    }
    mScoreText.setString(text);
}

}  // namespace game_view