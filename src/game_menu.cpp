#include "game_menu.h"

namespace game_view {

Menu::Menu(sf::RenderWindow &window_) : title("Carcassonne-Game", getFont(), 30), invitation("", getFont(), 20),
      textEntered("", getFont(), 20), window(window_) {
    startSprite.setTexture(*getTextures().get_texture(game_view::textures::ID::STARTTEXTURE));
    startSprite.setPosition(100, 10);

    background.setTexture(*getTextures().get_texture(game_view::textures::ID::BACKGROUND));
    background.setPosition(0,0);

    title.setFillColor(sf::Color::Black);
    invitation.setFillColor(sf::Color::Black);
    textEntered.setFillColor(sf::Color::Black);

    title.setPosition(120,50);
    invitation.setPosition(120,120);
    textEntered.setPosition(120, 160);
}

void Menu::handle_event(sf::Event &event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    if(!numberReceived){
        if (event.type == sf::Event::TextEntered) {
            stringEntered = event.text.unicode;
            textEntered.setString(stringEntered);
            std::string tmpString = stringEntered;
            numberOfPlayers = std::stoi(tmpString);
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter &&
                numberOfPlayers > 1 && numberOfPlayers < 6) {
                numberReceived = true;
                return;
            }
        }
    }
    else {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode > 47 && event.text.unicode < 123) {
                stringEntered += event.text.unicode;
                textEntered.setString(stringEntered);
            }
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter){
                players.emplace_back(stringEntered, game_model::colorsVector[counter-1]);
                counter ++;
                stringEntered = "";
                textEntered.setString("");
            }
            if(event.key.code == sf::Keyboard::BackSpace) {
                stringEntered.erase(stringEntered.getSize()-1);
                textEntered.setString(stringEntered);
            }
        }
    }
}

void Menu::render() const {
    window.clear();
    window.draw(background);
    window.draw(startSprite);
    window.draw(title);
    window.draw(invitation);
    window.draw(textEntered);
    window.display();
}

std::vector<std::pair<std::string, game_model::Color>> Menu::init_players() {
    invitation.setString("Enter number of players");
    sf::Event event{};
    while (window.isOpen() && !numberReceived) {
        while (window.pollEvent(event)) {
            handle_event(event);
        }
        render();
    }
    textEntered.setString("");

    while (window.isOpen() && counter <= numberOfPlayers) {
        invitation.setString("Player " + std::to_string(counter) +
                             "\nEnter your name:");
        while (window.pollEvent(event)) {
            handle_event(event);
        }
        render();
    }

    return players;
}

}// game_view