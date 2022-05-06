#include "interaction.h"
#include <iostream>

namespace interaction {

void defaultInteraction::handleEvent(sf::Event &event, bool &endOfState) {
    defaultInterfaceInteraction(event);
    if (event.type == sf::Event::MouseButtonPressed) {
        endOfState = true;
    }
}

void defaultInteraction::defaultInterfaceInteraction(sf::Event &event) {
    if (event.type == sf::Event::Closed) {
        mWindow->close();
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            mainView->getView().move(-10, 0);
        }

        if (event.key.code == sf::Keyboard::Up) {
            mainView->getView().move(0, -10);
        }

        if (event.key.code == sf::Keyboard::Down) {
            mainView->getView().move(0, 10);
        }
        if (event.key.code == sf::Keyboard::Right) {
            mainView->getView().move(10, 0);
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            mainView->getView().zoom(
                static_cast<float>(1.0 + 0.1 * event.mouseWheelScroll.delta));
            event.type = sf::Event::JoystickMoved;
        }
    }
}

void cardPlacementInteraction::handleEvent(sf::Event &event, bool &endOfState) {
    defaultInterfaceInteraction(event);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            (*currentCard)->rotateLeft();
        }
        if (event.key.code == sf::Keyboard::D) {
            (*currentCard)->rotateRight();
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f worldCoords = mWindow->mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y},
                mainView->getView());

             if
             (gameBoard->canAddCard(game_view::to_tiles_coords(worldCoords),
             **currentCard)) {
            gameBoard->addCard(game_view::to_tiles_coords(worldCoords),
                               **currentCard);
                sf::Vector2f spritePos = game_view::align_card_coords(worldCoords);
                (*currentCard)->setSpritePos(spritePos);
                endOfState = true;
            } else {
                // something
            }
        }
    }
}

void unitPlacementInteraction::handleEvent(sf::Event &event, bool &endOfState) {
    defaultInterfaceInteraction(event);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            endOfState = true;
            return;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i clickCoordinates(mainView->getView().getCenter());
            clickCoordinates.x +=
                (event.mouseButton.x -
                 static_cast<int>(mainView->getView().getSize().x / 2));
            clickCoordinates.y +=
                (event.mouseButton.y -
                 static_cast<int>(mainView->getView().getSize().y / 2));

            gameBoard->getTiles()[clickCoordinates].unit =
                currentPlayer->get_unit();
            gameBoard->getTiles()[clickCoordinates].unit->tile =
                &gameBoard->getTiles()[clickCoordinates];
        }
    }
}

}  // namespace interaction