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

    bool host;
    std::vector<std::string> players_list;

public:
    explicit Menu(sf::RenderWindow &window_);
    bool execute_start(); // returns true if client chose to be a host, otherwise false - connect to a host
    int ask_port();
    sf::String ask_IP();
    std::pair<sf::String, int> ask_name_color(const std::vector<int>& available_colors);
    bool lobby();
    void set_host(bool host_) {
        host = host_;
    }
    void set_list(const std::vector<std::string> &players_list_){
        players_list = players_list_;
    }

};

} // game_view
#endif // GAME_MENU_H_