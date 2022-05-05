#include "game_menu.h"

namespace game_view {


Menu::Menu(sf::RenderWindow &window_) :  window(window_) {

    background.setTexture(*getTextures().get_texture(game_view::textures::ID::BACKGROUND));
    background.setPosition(0,0);

    startTexture.loadFromFile("menu/gamestart.jpg");
    startSprite.setTexture(startTexture);
    startSprite.setPosition(startSprPos);

    title.setTexture(*getTextures().get_texture(game_view::textures::ID::TITLE));
    title.setPosition(startSprPos.x + 100,5);

}

std::vector<std::pair<sf::String, game_model::Color>> Menu::start_game() {
    execute_start();
    get_players(get_number());

    return players;
}

void Menu::execute_start() {
    bool end = false;
    bool new_game;
    sf::Event event{};
    sf::Texture bigTitleTexture;
    bigTitleTexture.loadFromFile("menu/carcasonne_title_big.png");
    sf::Sprite bigTitle;
    bigTitle.setTexture(bigTitleTexture);
    bigTitle.setPosition(150,30); // 735 x 200
    sf::Text invitation("New Game", getFont(), 70);
    invitation.setPosition(350,350); // 320 x 70

    while (window.isOpen() && !end ) {
        invitation.setFillColor(sf::Color::White);
        new_game = false;
        window.clear();

        if (sf::IntRect(350, 350, 320, 70).contains(sf::Mouse::getPosition(window))) {
            invitation.setFillColor(sf::Color( 133, 193, 233));
            new_game = true;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && new_game) {
            end = true;
        }
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.draw(background);
        window.draw(bigTitle);
        window.draw(invitation);
        window.display();

    }
}

int Menu::get_number() {
    int numberOfPlayers = 0;
    int tmpNumber = 0;
    bool numberReceived = false;
    bool wrongNum = false;
    sf::Event event{};
    sf::String stringEntered;


    sf::Text invitation("Enter number of players from 2 to 5", getFont(), 35);
    invitation.setFillColor(sf::Color::Black);
    sf::Vector2f invPos = {startSprPos.x + 20, startSprPos.y + 50};
    invitation.setPosition(invPos);

    sf::Text wrongNumber("The number of players should be\n from 2 to 5 :(", getFont(), 35);
    wrongNumber.setFillColor(sf::Color(  123, 36, 28  ));
    wrongNumber.setPosition(invPos.x, invPos.y + 100);

    sf::Text textEntered("",getFont(), 40);
    textEntered.setFillColor(sf::Color::Black);
    textEntered.setPosition(invPos.x + 70, invPos.y + 100);


    while (window.isOpen() && !numberReceived ) {

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                stringEntered = event.text.unicode;
                textEntered.setString(stringEntered);
                std::string tmpString = stringEntered;
                try {
                    tmpNumber = std::stoi(tmpString);
                    wrongNum = false;
                } catch (std::invalid_argument &) {
                    tmpNumber = 0;
                    stringEntered = "";
                    textEntered.setString(stringEntered);
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::BackSpace) {
                    stringEntered.erase(stringEntered.getSize()-1);
                    textEntered.setString(stringEntered);
                }
                else if (event.key.code == sf::Keyboard::Enter){
                    if( tmpNumber < 2 || tmpNumber > 5){
                        wrongNum = true;
                        stringEntered = "";
                        textEntered.setString(stringEntered);
                    }
                    else {
                        numberOfPlayers = tmpNumber;
                        numberReceived = true;
                    }
                }
            }
        }

        window.draw(background);
        window.draw(startSprite);
        window.draw(title);
        window.draw(invitation);
        if(!wrongNum) {
            window.draw(textEntered);
        } else {
            window.draw(wrongNumber);
        }
        window.display();

    }
    return numberOfPlayers;
}

struct Colors {
    int number = -1;
    std::vector<std::pair<sf::RectangleShape, bool>> colors;
    explicit Colors(sf::Vector2f startSprPos) {
        colors.resize(5);
        colors[0].first.setFillColor(sf::Color( 203, 45, 26 )); //RED
        colors[1].first.setFillColor(sf::Color( 241, 196, 15 )); //YELLOW
        colors[2].first.setFillColor(sf::Color( 39, 145, 23 )); //GREEN
        colors[3].first.setFillColor(sf::Color( 36, 113, 163 )); //BLUE
        colors[4].first.setFillColor(sf::Color::Black);

        float xPos = startSprPos.x + 20;
        float yPos = startSprPos.y + 270;
        for(int i = 0; i < 5; i++){
            colors[i].first.setSize({96,96});
            colors[i].first.setPosition(xPos, yPos);
            xPos += 116;
            colors[i].first.setOutlineThickness(0);
            colors[i].first.setOutlineColor(sf::Color::White);
        }
    }

    void draw(sf::RenderWindow &target) {
        for (int i = 0; i < 5; i++ ) {
            if(colors[i].second) {
                continue;
            }
            sf::RectangleShape rect = colors[i].first;
            if(sf::IntRect(rect.getPosition().x, rect.getPosition().y, rect.getSize().x, rect.getSize().y).contains(
                    sf::Mouse::getPosition(target))) {
            }
            target.draw(rect);
        }
    }

    void pick(sf::RenderWindow &window){
        for (int i = 0; i < 5; i++ ) {
            if (colors[i].second) {
                continue;
            }
            sf::RectangleShape rect = colors[i].first;
            if (sf::IntRect(rect.getPosition().x, rect.getPosition().y,
                            rect.getSize().x, rect.getSize().y).contains(sf::Mouse::getPosition(window)) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if(number != -1) {
                    colors[number].first.setOutlineThickness(0);
                }
                colors[i].first.setOutlineThickness(5);
                number = i;
            }
        }
    }

};

void Menu::get_players( int number ) {
    int counter = 1;
    sf::Event event{};
    sf::String stringEntered;
    bool wrongN = false;
    bool noCol = false;

    Colors cols(startSprPos);

    sf::Text invitation1("", getFont(), 35);
    invitation1.setFillColor(sf::Color::Black);
    sf::Vector2f invPos = {startSprPos.x + 20, startSprPos.y + 20};
    invitation1.setPosition(invPos);

    sf::Text invitation2("Choose your colour", getFont(), 35);
    invitation2.setFillColor(sf::Color::Black);
    invitation2.setPosition(invPos.x , invPos.y + 150);

    sf::Text textEntered("", getFont(), 45);
    textEntered.setFillColor(sf::Color(123, 36, 28));
    textEntered.setPosition(invPos.x + 70, invPos.y + 80);

    sf::Text wrongName("You have not entered a name yet", getFont(), 35);
    wrongName.setFillColor(sf::Color(  123, 36, 28  ));
    wrongName.setPosition(invPos.x, invPos.y + 80);

    sf::Text noColor("You have not chosen a colour yet", getFont(), 35);
    noColor.setFillColor(sf::Color(  123, 36, 28  ));
    noColor.setPosition(invPos.x, invPos.y + 190);

    while (window.isOpen() && counter <= number) {
        window.clear();
        cols.pick(window);
        if ( cols.number != -1) {
            noCol = false;
        }
        invitation1.setString("Player " + std::to_string(counter) +
                             "\nEnter your name:");

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode > 47 && event.text.unicode < 123) {
                    wrongN = false;
                    stringEntered += event.text.unicode;
                    textEntered.setString(stringEntered);
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    stringEntered.erase(stringEntered.getSize() - 1);
                    textEntered.setString(stringEntered);
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (stringEntered == "") {
                        wrongN = true;
                        continue ;
                    }
                    if (cols.number == -1) {
                        noCol = true;
                        continue ;
                    }
                    players.emplace_back(stringEntered,
                                         game_model::colorsVector[cols.number]);
                    cols.colors[cols.number].second = true;
                    cols.number = -1;
                    counter++;
                    stringEntered = "";
                    textEntered.setString("");
                }
            }
        }

    window.draw(background);
    window.draw(startSprite);
    window.draw(title);
    window.draw(invitation1);
    window.draw(invitation2);
    window.draw(textEntered);
    if(wrongN) {
        window.draw(wrongName);
    }
    if(noCol) {
        window.draw(noColor);
    }
    cols.draw(window);

    window.display();
}

}

}// game_view