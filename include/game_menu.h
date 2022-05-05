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

    std::vector<std::pair<sf::String, game_model::Color>> players;

    void execute_start();
    int get_number();
    void get_players(int number);

public:
    explicit Menu(sf::RenderWindow &window_);
    std::vector<std::pair<sf::String, game_model::Color>> start_game();

};

} // game_view
#endif // GAME_MENU_H_