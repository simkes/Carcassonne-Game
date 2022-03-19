#include "game.h"
#include <algorithm>

namespace carcassonne_game {

std::deque <Card> init_cardDeck() {
    std::deque <Card> cardDeck;

    for(int i = 1; i < 22; i++){
        std::string filename = "cardsdata/" + std::to_string(i) + ".txt";
        if(i < 3){
            for (int j = 0; j < 9; j++){
                cardDeck.emplace_back(Card(filename, i));
            }
        }
        else {
            for (int j = 0; j < 4; j++){
                cardDeck.emplace_back(Card(filename, i));
            }
        }
    }

    std::shuffle(cardDeck.begin(), cardDeck.end(), rand());
    return cardDeck;
}

std::vector<std::pair<int,int>> cardsToLoad{{0,0}, {0,1}, {0,2}, {0,3},
                                             {1,0}, {1,2}, {1,3},{2,1},
                                             {2,3}, {3,0}, {3,1},{3,2},
                                             {4,1}, {4,3}, {5,0}, {5,1},
                                             {1,0}, {1,2}, {4,1}, {4,2},
                                             {4,3}}; // TODO: make in file?

void init_textures(TextureHolder &textures) {
    int textureID = 1;
    std::string filename = "cardsTextures1-16.png";
    for(; textureID < 17; textureID++){
        int x = cardsToLoad[textureID-1].first;
        int y = cardsToLoad[textureID-1].second;
        textures.load(textureID, filename, x * CARDTEXTURESIZE,
                      y * CARDTEXTURESIZE, CARDTEXTURESIZE,
                      CARDTEXTURESIZE);
    }

    filename = "cardsTextures17-21.png";
    for(; textureID < 22; textureID++){
        int x = cardsToLoad[textureID-1].first;
        int y = cardsToLoad[textureID-1].second;
        textures.load(textureID, filename, x * CARDTEXTURESIZE,
                      y * CARDTEXTURESIZE, CARDTEXTURESIZE,
                      CARDTEXTURESIZE);
    }

}

Game::Game(std::vector<Player> players): mPlayers(std::move(players)),
      mWindow(sf::VideoMode(640, 480), "Carcassonne-Game"/*, sf::Style::Fullscreen*/),
      numberOfPlayers(mPlayers.size()),
      mBoardView(mBoard) {
    cardDeck = std::move(init_cardDeck());
    init_textures(textures);
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
    mBoardView.draw(mWindow,sf::RenderStates::Default); //TODO: RenderStates ??
    mWindow.display();
}


} // namespace carcassonne_game