#include "game.h"
#include <algorithm>

namespace carcassonne_game {

std::deque <Card> init_cardDeck() {
    std::deque <Card> cardDeck;

    for(int i = 1; i < 22; i++){
        std::string filename = std::to_string(i) + ".txt";
        if(i < 3){
            for (int j = 0; j < 9; j++){
                cardDeck.emplace_back(Card(filename));
            }
        }
        else {
            for (int j = 0; j < 4; j++){
                cardDeck.emplace_back(Card(filename));
            }
        }
    }

    std::shuffle(cardDeck.begin(), cardDeck.end(), rand());
    return cardDeck;
}

Game::Game(std::vector<Player> players): mPlayers(std::move(players)),
      mWindow(sf::VideoMode(640, 480), "Carcassonne-Game"/*, sf::Style::Fullscreen*/),
      numberOfPlayers(mPlayers.size())  {
    cardDeck = std::move(init_cardDeck());
}

void Game::run() {
    while (mWindow.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    if(currentState == State::DEFAULT){
        currentPlayer = (currentPlayer++) % numberOfPlayers;
        currentState = State::CARDPLACEMENT;
    }
    sf::Event event;
    while(mWindow.pollEvent(event)) {
        interaction->handleEvent(event);
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(BoardView(mBoard));
    mWindow.display();
}


} // namespace carcassonne_game