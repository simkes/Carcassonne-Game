#include "interaction.h"

namespace interaction {

void defaultInteraction::handleEvent(sf::Event &event, bool &endOfState) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            mainView.getView().move(-10, 0);
        }

        if (event.key.code == sf::Keyboard::Up) {
            mainView.getView().move(0, 10);
        }

        if (event.key.code == sf::Keyboard::Down) {
            mainView.getView().move(0, -10);
        }

        if (event.key.code == sf::Keyboard::Right) {
            mainView.getView().move(10, 0);
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            mainView.getView().zoom(
                static_cast<float>(1.0 + 0.1 * event.mouseWheelScroll.delta));
        }
    }
    // endOfState = true; ???
}

void cardPlacementInteraction::handleEvent(sf::Event &event, bool &endOfState) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            mainView.getView().move(-10, 0);
        }

        if (event.key.code == sf::Keyboard::Up) {
            mainView.getView().move(0, 10);
        }

        if (event.key.code == sf::Keyboard::Down) {
            mainView.getView().move(0, -10);
        }

        if (event.key.code == sf::Keyboard::Right) {
            mainView.getView().move(10, 0);
        }

        if (event.key.code == sf::Keyboard::Q) {
            currentCard->rotateLeft();
        }

        if (event.key.code == sf::Keyboard::E) {
            currentCard->rotateRight();
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            mainView.getView().zoom(
                static_cast<float>(1.0 + 0.1 * event.mouseWheelScroll.delta));
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i clickCoordinates(mainView.getView().getCenter());
            clickCoordinates.x +=
                (event.mouseButton.x -
                 static_cast<int>(mainView.getView().getSize().x / 2));
            clickCoordinates.y +=
                (event.mouseButton.y -
                 static_cast<int>(mainView.getView().getSize().y /
                                  2));  // TODO: make coordinate convert easier

            if (gameBoard.canAddCard(clickCoordinates, *currentCard)) {
                gameBoard.addCard(clickCoordinates, *currentCard);
                endOfState = true;
            }  // what to do with else: error? warning? nothing?
        }
    }
}

void unitPlacementInteraction::handleEvent(sf::Event &event, bool &endOfState) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            endOfState = true;
            return;
        }

        if (event.key.code == sf::Keyboard::Left) {
            mainView.getView().move(-10, 0);
        }

        if (event.key.code == sf::Keyboard::Up) {
            mainView.getView().move(0, 10);
        }

        if (event.key.code == sf::Keyboard::Down) {
            mainView.getView().move(0, -10);
        }

        if (event.key.code == sf::Keyboard::Right) {
            mainView.getView().move(10, 0);
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            mainView.getView().zoom(
                static_cast<float>(1.0 + 0.1 * event.mouseWheelScroll.delta));
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i clickCoordinates(mainView.getView().getCenter());
            clickCoordinates.x +=
                (event.mouseButton.x -
                 static_cast<int>(mainView.getView().getSize().x / 2));
            clickCoordinates.y +=
                (event.mouseButton.y -
                 static_cast<int>(mainView.getView().getSize().y / 2));

            gameBoard.getTiles()[clickCoordinates].unit =
                currentPlayer->get_unit();
            gameBoard.getTiles()[clickCoordinates].unit->tile =
                &gameBoard.getTiles()[clickCoordinates];
        }
    }
}

}  // namespace mInteraction