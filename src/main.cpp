#include "game.h"
#include <iostream>
using namespace game_model;

std::map <std::string, Color> mColors{ {"Red", Color::RED}, {"Yellow",Color::YELLOW}, {"Green",Color::GREEN}, {"Blue",Color::BLUE}, {"Black",Color::BLACK} };

std::vector<Player> init_players(int numberOfPlayers){ // вот эту функцию надо потом будет нормально через sfml оформить
    std::vector<Player> result;
    for(int i = 0; i < numberOfPlayers; i++){
        std::string name;
        std::string color;
        std::cin >> name >> color;
        result.emplace_back(Player(name,mColors[color]));
    }
   return result;
}

int main(){
int numberOfPlayers;
std::cin >> numberOfPlayers; // sfml
carcassonne_game:: Game newGame(init_players(numberOfPlayers));
newGame.run();
}