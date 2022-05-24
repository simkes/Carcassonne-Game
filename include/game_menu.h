#ifndef GAME_MENU_H_
#define GAME_MENU_H_

#include "game_view.h"

namespace game_view {

struct Menu {
private:
    sf::RenderWindow &window;

    sf::Sprite title;
    sf::Texture startTexture;
    sf::Sprite startSprite;
    sf::Sprite background;
    sf::Vector2f startSprPos = {212, 150};

  //  int get_number();
   // void get_players(int number);

public:
    explicit Menu(sf::RenderWindow &window_);
    bool execute_start(); // returns true if client chose to be a host, otherwise false - connect to a host
    int ask_port();
    sf::String ask_IP();


};

} // game_view
#endif // GAME_MENU_H_