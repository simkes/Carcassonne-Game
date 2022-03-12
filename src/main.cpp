#include "game.h"
using namespace game_model;

sf::RenderWindow startWindow(sf::VideoMode(640,480), "Carcassonne-Game");

std::map <int, Color> colorsMap{ {1, Color::RED}, {2,Color::YELLOW}, {3,Color::GREEN}, {4,Color::BLUE}, {5,Color::BLACK} };

int getNumberOfPlayers(sf::Text &invitation, sf::Text &textEntered, sf::Sprite &startSprite, sf::Text &title) {

    int numberOfPlayers = 0;
    sf::String stringEntered;
    sf::Event event;
    invitation.setString("Enter number of players");

    while (startWindow.isOpen()) {

        while (startWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                startWindow.close();
            if (event.type == sf::Event::TextEntered) {
                stringEntered = event.text.unicode;
                textEntered.setString(stringEntered);
                std::string tmpString = stringEntered;
                numberOfPlayers = std::stoi(tmpString);
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter &&
                    numberOfPlayers > 1 && numberOfPlayers < 6) {
                    return numberOfPlayers;
                }
            }
        }

        startWindow.clear();
        startWindow.draw(startSprite);
        startWindow.draw(title);
        startWindow.draw(invitation);
        startWindow.draw(textEntered);
        startWindow.display();
    }

}

void init_players(std::vector<Player> players, int numberOfPlayers,sf::Text &invitation, sf::Text &textEntered, sf::Sprite &startSprite, sf::Text &title){

        sf::String stringEntered;
        textEntered.setString("");
        sf::Event event;
        int counter = 1;

        while (startWindow.isOpen() && counter <= numberOfPlayers) {

            invitation.setString("Player " + std::to_string(counter) + "\nEnter your name:");

            while(startWindow.pollEvent(event)){

            if (event.type == sf::Event::Closed)
                startWindow.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode > 47 && event.text.unicode < 123) {
                    stringEntered += event.text.unicode;
                    textEntered.setString(stringEntered);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter){
                    players.emplace_back(stringEntered, colorsMap[counter]);
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

        startWindow.clear();
        startWindow.draw(startSprite);
        startWindow.draw(title);
        startWindow.draw(invitation);
        startWindow.draw(textEntered);
        startWindow.display();
    }
}

std::vector<Player> start_game(){
    std::vector<Player> players;

    sf::Texture startTexture;
    startTexture.loadFromFile("gamestart.jpg"); // TODO: вынести в TextureHolder
    sf::Sprite startSprite;
    startSprite.setTexture(startTexture);
    startSprite.setTextureRect(sf::IntRect(0, 0, 340, 510));
    startSprite.setPosition(100, 10);

    sf::Font font;
    font.loadFromFile("CyrilicOld.TTF"); // TODO: потом надо будет шрифт куда-то в более общее место загрузить, чтобы потом в view использовать

    sf::Text title("Carcassonne-Game",  font, 30);
    title.setColor(sf::Color::Black);
    title.setPosition(120,50);

    sf::Text invitation("",  font, 20);
    invitation.setColor(sf::Color::Black);
    invitation.setPosition(120,120);

    sf::Text textEntered("",  font, 20);
    textEntered.setColor(sf::Color::Black);
    textEntered.setPosition(120, 160);

    int numberOfPlayers = getNumberOfPlayers(invitation, textEntered, startSprite, title);
    init_players(players, numberOfPlayers, invitation, textEntered, startSprite, title);

    return players;
}

int main(){
 carcassonne_game:: Game newGame(std::move(start_game()));
 newGame.run();
}