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

            if (gameBoard->canAddCard(game_view::to_tiles_coords(worldCoords),
                                      **currentCard)) {
                gameBoard->addCard(game_view::to_tiles_coords(worldCoords),
                                   **currentCard);
                sf::Vector2f spritePos =
                    game_view::align_card_coords(worldCoords);
                (*currentCard)->setSpritePos(spritePos);
                endOfState = true;
            } else {
                // something
            }
        }
    }
}

void unitPlacementInteraction::setCurrentPlayer(game_model::Player *newPlayer) {
    currentPlayer = newPlayer;
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
        if (!currentPlayer->get_unit()) {
            return;
        }

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
                game_view::to_tiles_coords(mWindow->mapPixelToCoords(
                    {event.mouseButton.x, event.mouseButton.y},
                    mainView->getView()));

            game_model::Tile &currentTile =
                gameBoard->getTiles()[worldCoords].get();

            if (currentTile.type == game_model::Type::NOTHING ||
                currentTile.type == game_model::Type::JUNCTION ||
                currentTile.type == game_model::Type::CASTLEWITHSHIELD) {
                // may be text in window
            } else {
                currentTile.unit = currentPlayer->get_unit();
                currentTile.unit->tile = &currentTile;

                /*gameBoard->getTiles()[worldCoords].unit =
                    currentPlayer->get_unit();
                gameBoard->getTiles()[worldCoords].unit->tile =
                    &gameBoard->getTiles()[worldCoords];*/
            }
        }
    }
}

}  // namespace interaction