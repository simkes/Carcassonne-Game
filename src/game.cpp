#include "game.h"
#include <algorithm>
#include <random>
std::mt19937 rng (239);

namespace carcassonne_game {

int get_numberOfPlayers(sf::RenderWindow &gameWindow, sf::Text &invitation, sf::Text &textEntered, sf::Sprite &startSprite, sf::Sprite &background, sf::Text &title) {

    int numberOfPlayers = 0;
    sf::String stringEntered;
    sf::Event event;

    invitation.setString("Enter number of players");

    while (gameWindow.isOpen()) {

        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gameWindow.close();
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

        gameWindow.clear();
        gameWindow.draw(background);
        gameWindow.draw(startSprite);
        gameWindow.draw(title);
        gameWindow.draw(invitation);
        gameWindow.draw(textEntered);
        gameWindow.display();
    }

    return 0;
}

void init_mPlayers(sf::RenderWindow &gameWindow, std::vector<Player> &players, std::size_t numberOfPlayers, sf::Text &invitation, sf::Text &textEntered, sf::Sprite &startSprite, sf::Sprite &background, sf::Text &title){

    sf::String stringEntered;
    sf::Event event;

    textEntered.setString("");
    int counter = 1;

    while (gameWindow.isOpen() && counter <= numberOfPlayers) {

        invitation.setString("Player " + std::to_string(counter) + "\nEnter your name:");

        while(gameWindow.pollEvent(event)){

            if (event.type == sf::Event::Closed)
                gameWindow.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode > 47 && event.text.unicode < 123) {
                    stringEntered += event.text.unicode;
                    textEntered.setString(stringEntered);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter){
                    players.emplace_back(stringEntered, colorsVector[counter-1]);
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

        gameWindow.clear();
        gameWindow.draw(background);
        gameWindow.draw(startSprite);
        gameWindow.draw(title);
        gameWindow.draw(invitation);
        gameWindow.draw(textEntered);
        gameWindow.display();
    }
}

void Game::init_players() {

    sf::Sprite startSprite;
    sf::Text title("Carcassonne-Game",  font, 30);
    sf::Text invitation("",  font, 20);
    sf::Text textEntered("",  font, 20);

    startSprite.setTexture(*Textures.get_texture(game_view::textures::ID::STARTTEXTURE));

    startSprite.setPosition(100, 10);

    title.setFillColor(sf::Color::Black);
    invitation.setFillColor(sf::Color::Black);
    textEntered.setFillColor(sf::Color::Black);
    
    title.setPosition(120,50);
    invitation.setPosition(120,120);
    textEntered.setPosition(120, 160);

    numberOfPlayers = get_numberOfPlayers(mWindow, invitation, textEntered, startSprite, background, title);
    init_mPlayers(mWindow, mPlayers, numberOfPlayers, invitation, textEntered, startSprite, background, title);
}

void Game::init_cardDeck() {
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

    std::shuffle(cardDeck.begin(), cardDeck.end(), rng);
}

void Game::init_interaction() {
    interaction.emplace(State::DEFAULT, std::make_unique<defaultInteraction>(mBoardView));
    interaction.emplace(State::CARDPLACEMENT, std::make_unique<cardPlacementInteraction>(mBoardView, &mBoard, currentCardPtr));
    interaction.emplace(State::UNITPLACEMENT, std::make_unique<unitPlacementInteraction>(mBoardView, &mBoard, currentCardPtr, currentPlayerPtr));
}

Game::Game(): mWindow(sf::VideoMode(1024, 700), "Carcassonne-Game"/*, sf::Style::Fullscreen*/), mBoardView(mBoard) {

    background.setTexture(*Textures.get_texture(game_view::textures::ID::BACKGROUND));
    background.setPosition(0,0);

    init_players();
    init_cardDeck();
    init_interaction();

    currentPlayerPtr = &mPlayers[currentPlayerIndex];
}

void Game::run() {
    while (mWindow.isOpen())
    {
        process_events();
        update();
        render();
        change_state();
    }
}


void Game::process_events() {
    if(currentState == interaction::State::CARDPLACEMENT){
        execute_cardPlacement();
    }
    defaultInteraction *currentInteraction = interaction[currentState].get();
    sf::Event event;
    while(mWindow.pollEvent(event)) {
        currentInteraction->handleEvent(event);
    }
}

void Game::update() {
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(background);
    mBoardView.draw(mWindow,sf::RenderStates::Default); //TODO: RenderStates ??
    if(currentState==State::CARDPLACEMENT){
        CardView(*currentCardPtr, *Textures.get_texture(currentCardPtr->textureId < 17 ? textures::ID::CARDS1 : textures::ID::CARDS2 )).draw(mWindow, sf::RenderStates::Default);
    }
    mWindow.display();
}

void Game::change_state() {
    switch (currentState) {
        case State::DEFAULT:{
            currentPlayerIndex= (currentPlayerIndex++) % numberOfPlayers;
            currentPlayerPtr = &mPlayers[currentPlayerIndex];
            currentState = State::CARDPLACEMENT;
            break;
        }
        case State::CARDPLACEMENT:
            currentState = State::UNITPLACEMENT;
            break;
        case State::UNITPLACEMENT:
            currentState = State::DEFAULT;
            break;
    }
}
void Game::execute_cardPlacement() {
    placedCards.push_back(cardDeck.back());
    cardDeck.pop_back();
    currentCardPtr = &placedCards.back();
    currentCardPtr->id = static_cast<int>(placedCards.size()-1);
    currentCardPtr->setTiles();
}
void Game::execute_unitPlacement() {
    //TODO
}


} // namespace carcassonne_game