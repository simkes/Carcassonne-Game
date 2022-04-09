#ifndef GAME_MENU_H_
#define GAME_MENU_H_

#include "game_view.h"

namespace game_view {

struct Menu {
private:
    sf::RenderWindow &window;
    sf::Text title;
    sf::Text invitation;
    sf::Text textEntered;
    sf::String stringEntered;
    sf::Sprite startSprite;
    sf::Sprite background;
    int numberOfPlayers = 0; // delete
    int counter = 1;
    std::vector<std::pair<std::string, game_model::Color>> players;
    bool numberReceived = false;

    void handle_event(sf::Event &event);
public:
    explicit Menu(sf::RenderWindow &window_);
    void render() const;
    std::vector<std::pair<std::string, game_model::Color>> init_players();
};

} // game_view
#endif // GAME_MENU_H_