#include "interaction.h"
#include <iostream>

namespace interaction {

result defaultInteraction::handleEvent(sf::Event &event, bool &endOfState, bool &chat) {
    result defaultRes;
    defaultInterfaceInteraction(event, chat);
    if (event.type == sf::Event::MouseButtonPressed) {
        endOfState = true;
    }
    return defaultRes;
}

void defaultInteraction::defaultInterfaceInteraction(sf::Event &event, bool &chat) {
    if (event.type == sf::Event::Closed) {
        mRender->mWindow.close();
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            mRender->mBoardView.getView().move(-10, 0);
        }

        if (event.key.code == sf::Keyboard::Up) {
            mRender->mBoardView.getView().move(0, -10);
        }

        if (event.key.code == sf::Keyboard::Down) {
            mRender->mBoardView.getView().move(0, 10);
        }

        if (event.key.code == sf::Keyboard::Right) {
            mRender->mBoardView.getView().move(10, 0);
        }

        if (event.key.code == sf::Keyboard::C){
            chat = true;
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            mRender->mBoardView.getView().zoom(
                static_cast<float>(1.0 + 0.1 * event.mouseWheelScroll.delta));
            event.type = sf::Event::JoystickMoved;
        }
    }
}

result cardPlacementInteraction::handleEvent(sf::Event &event, bool &endOfState, bool &chat) {
    result cardRes;
    defaultInterfaceInteraction(event, chat);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            mRender->mCurCardView.rotate_L();
        }
        if (event.key.code == sf::Keyboard::D) {
            mRender->mCurCardView.rotate_R();
        }
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left ) {
        sf::Vector2f worldCoords = mRender->mWindow.mapPixelToCoords(
            {event.mouseButton.x, event.mouseButton.y},
            mRender->mBoardView.getView());
        cardRes.tile_coordinates = game_view::to_tiles_coords(game_view::align_card_coords(worldCoords));
        cardRes.card_rotation = mRender->mCurCardView.get_rotation();
        endOfState = true;
    }

    return cardRes;
}

result unitPlacementInteraction::handleEvent(sf::Event &event, bool &endOfState, bool &chat) {
    result unitRes;
    defaultInterfaceInteraction(event, chat);

    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Enter) {
        endOfState = true;
        return unitRes;
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left ) {
        sf::Vector2i worldCoords =
            game_view::to_tiles_coords(mRender->mWindow.mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y},
                mRender->mBoardView.getView()));

        unitRes.tile_coordinates = worldCoords;
        endOfState = true;
    }
    return unitRes;
}

std::string chatInteraction::handleEvent(sf::Event &event,
                                         bool &endOfState,
                                         bool &chat) {

    if (event.type == sf::Event::KeyPressed ) {
        if (event.key.code == sf::Keyboard::Escape) {
            chat = false;
            return "";
        }

        if (event.key.code == sf::Keyboard::BackSpace) {
            if (!message.empty()){
                message.erase(message.size() - 1);
                mRender->message = message;
            }
        }

        if (event.key.code == sf::Keyboard::Enter) {
            std::string resultMessage = message;
            message = "";
            endOfState = false;
            return resultMessage;
        }

    }

    if (event.type == sf::Event::TextEntered) {
        message += event.text.unicode;
        mRender->message = message;
    }

    return "";
}
}  // namespace interaction