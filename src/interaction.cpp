#include "interaction.h"

namespace interaction{

void defaultInteraction::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed){

        if (event.key.code == sf::Keyboard::Left){
            mainView.getView().move(-10, 0);
        }

        if (event.key.code == sf::Keyboard::Up){
            mainView.getView().move(0, 10);
        }

        if (event.key.code == sf::Keyboard::Down){
            mainView.getView().move(0, -10);
        }

        if (event.key.code == sf::Keyboard::Right){
            mainView.getView().move(10, 0);
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled){

        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
            mainView.getView().zoom(static_cast<float>(1.0 + 0.1 * event.mouseWheelScroll.delta));
        }

    }
}

void cardPlacementInteraction::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed){

        if (event.key.code == sf::Keyboard::Left){
            mainView.getView().move(-10, 0);
        }

        if (event.key.code == sf::Keyboard::Up){
            mainView.getView().move(0, 10);
        }

        if (event.key.code == sf::Keyboard::Down){
            mainView.getView().move(0, -10);
        }

        if (event.key.code == sf::Keyboard::Right){
            mainView.getView().move(10, 0);
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled){

        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
            mainView.getView().zoom(static_cast<float>(1.0 + 0.1 * event.mouseWheelScroll.delta));
        }

    }

    if (event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.button == sf::Mouse::Left){
            sf::Vector2i clickCoordinates(mainView.getView().getCenter());
            //clickCoordinates.x += (event.mouseButton.x - clickCoordinates.x);
            //clickCoordinates.y += (event.mouseButton.y - clickCoordinates.y); TODO: convert coordinate

            if (Board.canAddCard(clickCoordinates, currentCard)){
                Board.addCard(clickCoordinates, currentCard);
            } // what do with else: error? warning? nothing?
        }
    }
}

}