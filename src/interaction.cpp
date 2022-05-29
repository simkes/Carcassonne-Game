#include "interaction.h"
#include <iostream>

namespace interaction {

result defaultInteraction::handleEvent(sf::Event &event, bool &endOfState) {
    result defaultRes;
    defaultInterfaceInteraction(event);
    if (event.type == sf::Event::MouseButtonPressed) {
        endOfState = true;
    }
    return defaultRes;
}

void defaultInteraction::defaultInterfaceInteraction(sf::Event &event) {
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
    }

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            mRender->mBoardView.getView().zoom(
                static_cast<float>(1.0 + 0.1 * event.mouseWheelScroll.delta));
            event.type = sf::Event::JoystickMoved;
        }
    }
}

result cardPlacementInteraction::handleEvent(sf::Event &event, bool &endOfState) {
    result cardRes;
    defaultInterfaceInteraction(event);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            mRender->mCurCardView.rotate_L();
        }
        if (event.key.code == sf::Keyboard::D) {
            mRender->mCurCardView.rotate_R();
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f worldCoords = mRender->mWindow.mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y},
                mRender->mBoardView.getView());
            cardRes.tile_coordinates = game_view::to_tiles_coords(game_view::align_card_coords(worldCoords));
            cardRes.card_rotation = mRender->mCurCardView.get_rotation();
//                sf::Vector2f spritePos =
//                    game_view::align_card_coords(worldCoords);
//                (*currentCard)->setSpritePos(spritePos);
                endOfState = true;
            } else {
                // something
            }
        }
    return cardRes;
}

result unitPlacementInteraction::handleEvent(sf::Event &event, bool &endOfState) {
    result unitRes;
    defaultInterfaceInteraction(event);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            endOfState = true;
            return unitRes;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
//        if (!currentPlayer->get_unit()) { TODO: handle this
//            return unitRes;
//        }

        if (event.mouseButton.button == sf::Mouse::Right) {
            /*sf::Vector2f worldCoords = mWindow->mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y},
                mainView->getView());

            if (gameBoard->canAddCard(game_view::to_tiles_coords(worldCoords),
                                      **currentCard)) {
                gameBoard->addCard(game_view::to_tiles_coords(worldCoords),
                                   **currentCard);
                sf::Vector2f spritePos =
                    game_view::align_card_coords(worldCoords);
                (*currentCard)->setSpritePos(spritePos);
                endOfState = true;*/
            sf::Vector2i worldCoords =
                game_view::to_tiles_coords(mRender->mWindow.mapPixelToCoords(
                    {event.mouseButton.x, event.mouseButton.y},
                    mRender->mBoardView.getView()));

//            game_model::Tile &currentTile =
//                gameBoard->getTiles()[worldCoords].get(); TODO: and this

//            if (currentTile.type == game_model::Type::NOTHING ||
//                currentTile.type == game_model::Type::JUNCTION ||
//                currentTile.type == game_model::Type::CASTLEWITHSHIELD) {
//                // may be text in window
//            } else {
//                currentTile.unit = currentPlayer->get_unit();
//                currentTile.unit->tile = &currentTile;

                /*gameBoard->getTiles()[worldCoords].unit =
                    currentPlayer->get_unit();
                gameBoard->getTiles()[worldCoords].unit->tile =
                    &gameBoard->getTiles()[worldCoords];*/
//            }
        }
    }
    return unitRes;
}

}  // namespace interaction