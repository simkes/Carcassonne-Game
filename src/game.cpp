#include "game.h"

namespace carcassonne_game {

void Game::run() {
    while (mWindow.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)) // здесь interaction
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(BoardView(mBoard));
    mWindow.display();
}


} // namespace carcassonne_game