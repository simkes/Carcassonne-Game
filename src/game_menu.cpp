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

bool Menu::execute_start() { // returns true if client chose to be a host, otherwise false - connect to a host
    bool end = false;
    int button = 0; // 0 - nothing , 1 - be a host, 2 - connect
    sf::Event event{};
    sf::Texture bigTitleTexture;
    bigTitleTexture.loadFromFile("menu/carcasonne_title_big.png");
    sf::Sprite bigTitle;
    bigTitle.setTexture(bigTitleTexture);
    bigTitle.setPosition(150,30); // 735 x 200

    sf::Text be_host("Be a host", getFont(), 80); //TODO !!!
    be_host.setPosition(300,280); // 630 x 80
    sf::Text connect_to_host("Connect to a host", getFont(), 70);
    connect_to_host.setPosition(230,430); // 850 x 70

    while (window.isOpen() && !end ) {
        be_host.setFillColor(sf::Color::White);
        connect_to_host.setFillColor(sf::Color::White);
        button = 0;
        window.clear();

        if (sf::IntRect(300, 280, 630, 80).contains(sf::Mouse::getPosition(window))) {
            be_host.setFillColor(sf::Color( 133, 193, 233));
            button = 1;
        }
        else if (sf::IntRect(230, 430, 850, 70).contains(sf::Mouse::getPosition(window))) {
            connect_to_host.setFillColor(sf::Color( 133, 193, 233));
            button = 2;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button) {
            end = true;
        }
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.draw(background);
        window.draw(bigTitle);
        window.draw(be_host);
        window.draw(connect_to_host);
        window.display();

    }
    host = 2-button;
    return host;
}

int Menu::ask_port() {
    bool end = false;
    int port = 0;
    sf::Event event{};
    sf::String stringEntered;
    bool wrongP = false;

    sf::Text invitation("Enter port", getFont(), 40);
    invitation.setFillColor(sf::Color::Black);
    sf::Vector2f invPos = {startSprPos.x + 20, startSprPos.y + 20};
    invitation.setPosition(invPos);


    sf::Text textEntered("", getFont(), 45);
    textEntered.setFillColor(sf::Color(123, 36, 28));
    textEntered.setPosition(invPos.x + 70, invPos.y + 80);

    sf::Text wrongPort("You have not entered a port yet", getFont(), 35);
    wrongPort.setFillColor(sf::Color(  123, 36, 28  ));
    wrongPort.setPosition(invPos.x, invPos.y + 80);

    while (window.isOpen() && !end) {
        window.clear();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode > 47 && event.text.unicode < 58) {
                        wrongP = false;
                        stringEntered += event.text.unicode;
                        textEntered.setString(stringEntered);
                    }
                } else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::BackSpace) {
                        stringEntered.erase(stringEntered.getSize() - 1);
                        textEntered.setString(stringEntered);
                    } else if (event.key.code == sf::Keyboard::Enter) {
                        if (stringEntered == "") {
                            wrongP = true;
                            continue ;
                        }
                        port = std::stoi(stringEntered.operator std::string());
                        end = true;
                    }
                }
            }

        window.draw(background);
        window.draw(startSprite);
        window.draw(title);
        window.draw(invitation);
        window.draw(textEntered);
        if(wrongP) {
            window.draw(wrongPort);
        }
        window.display();
    }
    return port;
}

sf::String Menu::ask_IP() {
    sf::String ip;
    bool end = false;
    sf::Event event{};
    sf::String stringEntered;
    bool wrongIP = false;

    sf::Text invitation("Enter IP address", getFont(), 40);
    invitation.setFillColor(sf::Color::Black);
    sf::Vector2f invPos = {startSprPos.x + 20, startSprPos.y + 20};
    invitation.setPosition(invPos);


    sf::Text textEntered("", getFont(), 40);
    textEntered.setFillColor(sf::Color(123, 36, 28));
    textEntered.setPosition(invPos.x + 70, invPos.y + 80);

    sf::Text wrongIPadr("You have not entered an IP yet", getFont(), 35);
    wrongIPadr.setFillColor(sf::Color(  123, 36, 28  ));
    wrongIPadr.setPosition(invPos.x, invPos.y + 80);

    while (window.isOpen() && !end) {
        window.clear();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if ( (event.text.unicode > 47 && event.text.unicode < 58) || event.text.unicode == '.') {
                    wrongIP = false;
                    stringEntered += event.text.unicode;
                    textEntered.setString(stringEntered);
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    stringEntered.erase(stringEntered.getSize() - 1);
                    textEntered.setString(stringEntered);
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (stringEntered == "") {
                        wrongIP = true;
                        continue ;
                    }
                    ip = stringEntered;
                    end = true;
                }
            }
        }

        window.draw(background);
        window.draw(startSprite);
        window.draw(title);
        window.draw(invitation);
        window.draw(textEntered);
        if(wrongIP) {
            window.draw(wrongIPadr);
        }
        window.display();
    }
    return ip;
}

struct Colors {
    int number = -1;
    std::vector<std::pair<sf::RectangleShape, bool>> colors;
    explicit Colors (sf::Vector2f startSprPos, const std::vector<int>& available_colors) {
        colors.resize(5);
        colors[0].first.setFillColor(sf::Color( 203, 45, 26 )); //RED
        colors[1].first.setFillColor(sf::Color( 241, 196, 15 )); //YELLOW
        colors[2].first.setFillColor(sf::Color( 39, 145, 23 )); //GREEN
        colors[3].first.setFillColor(sf::Color( 36, 113, 163 )); //BLUE
        colors[4].first.setFillColor(sf::Color::Black);

        for(auto col : colors) {
            col.second = 1;
        }
        for(const auto& num : available_colors) {
            colors[num].second = 0;
        }

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

std::pair<sf::String, int> Menu::ask_name_color( const std::vector<int>& available_colors ) {
        bool end = false;
        sf::Event event{};
        sf::String stringEntered;
        bool wrongN = false;
        bool noCol = false;

        Colors cols(startSprPos,available_colors);

        sf::Text invitation1("Enter your name:", getFont(), 35);
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

        while (!end) {
            window.clear();
            cols.pick(window);
            if ( cols.number != -1) {
                noCol = false;
            }

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
                        end = true;
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
    return {stringEntered,cols.number};
}
bool Menu::lobby() {
    bool game_started = false;
    bool button = false;
    sf::Event event{};

    sf::String names_list = "";
    for(const auto &s : players_list) {
        names_list += s + '\n';
    }

    sf::Text list(names_list, getFont(), 40);
    list.setFillColor(sf::Color::Black);
    sf::Vector2f listPos = {startSprPos.x + 20, startSprPos.y + 20};
    list.setPosition(listPos);

    sf::Text invitation("Start Game", getFont(), 70);
    invitation.setPosition(startSprPos.x + 20, startSprPos.y + 350); // 350 x 70

        if(host) {
            invitation.setFillColor(sf::Color::White);
            button = false;
            window.clear();

            if (sf::IntRect(350, 350, 320, 70)
                    .contains(sf::Mouse::getPosition(window))) {
                invitation.setFillColor(sf::Color(133, 193, 233));
                button = true;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button) {
                game_started = true;
            }
        }

        window.draw(background);
        window.draw(startSprite);
        window.draw(title);
        window.draw(list);
        if(host) {
            window.draw(invitation);
        }
        window.display();

    return game_started;
}

}// game_view