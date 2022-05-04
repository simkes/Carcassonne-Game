#include "game.h"

namespace carcassonne_game {

void Game::init_players(std::vector<std::pair<std::string, game_model::Color>> &players) {
numberOfPlayers = players.size();
for(const auto &p : players){
    mPlayers.emplace_back(p.first,p.second);
}
}

void Game::init_interaction() {
    mInteraction.emplace(State::DEFAULT, std::make_unique<defaultInteraction>(mBoard, mGameRenderPtr->get_boardView(), mGameRenderPtr->window()));
    mInteraction.emplace(State::CARDPLACEMENT, std::make_unique<cardPlacementInteraction>(mBoard, mGameRenderPtr->get_boardView(), &currentCardPtr, mGameRenderPtr->window()));
    mInteraction.emplace(State::UNITPLACEMENT, std::make_unique<unitPlacementInteraction>(mBoard, mGameRenderPtr->get_boardView(), currentCardPtr, currentPlayerPtr, mGameRenderPtr->window()));
}

void Game::set_currentCard() {
    if(mCardDeck.empty()) {
        gameOver = true; // TODO: make end of game with score counted
        return;
    }
    Card newCard = mCardDeck.get_card();
    newCard.id = static_cast<int>(placedCards.size());
    placedCards.push_back(newCard);
    placedCards.back().setTiles();
    int textureId = placedCards.back().textureId;
    placedCards.back().setSprite(*getTextures().get_texture(textureId < 17 ? textures::ID::CARDS1 : textures::ID::CARDS2));
    placedCards.back().setSpritePos({874,124});
    currentCardPtr = &placedCards.back();
}

void Game::place_first_card() {
    set_currentCard();
    sf::Vector2i pos(102,102);
    currentCardPtr->setSpritePos({3074,3074});
    mBoard.addCard(pos,*currentCardPtr);
}

Game::Game(std::vector<std::pair<std::string, game_model::Color>> players, GameRender *gameRenderPtr) : mGameRenderPtr(gameRenderPtr) {
    mGameRenderPtr->set_boardView(&mBoard);
    placedCards.reserve(100);
    init_players(players);
    init_interaction();
    place_first_card();
    //currentState = State::UNITPLACEMENT;
    currentState = State::DEFAULT;
    currentPlayerPtr = &mPlayers[currentPlayerIndex];
}

void Game::run() {
    while(!gameOver) {
        if(currentState == State::CARDPLACEMENT){
            set_currentCard();
        }
        sf::Event event;
        while (mGameRenderPtr->window().isOpen() && !endOfState) {
            process_events(event);
            update();
            render();
        }
        change_state();
    }
}


void Game::process_events(sf::Event &event) {
    while(mGameRenderPtr->window().pollEvent(event)) {
        mInteraction[currentState]->handleEvent(event, endOfState);
//        switch (event.type) {
//            case sf::Event::Closed:
//                mGameRenderPtr->window().close();
//                break;
//            case sf::Event::MouseButtonPressed: {
//
//                if(currentState == State::CARDPLACEMENT) {
//                    if (event.mouseButton.button == sf::Mouse::Left) {
//                        sf::Vector2i position = sf::Mouse::getPosition(mGameRenderPtr->window());
//                        sf::Vector2i cardPos =
//                            mBoard.getEmptyPosition(position);
//                        sf::Vector2f cardSpritePos = transform_coordinates({(cardPos.x/(CARD_DIMENSION-1))*textures::CARD_TEXTURE_SIZE + 74, (cardPos.y/(CARD_DIMENSION-1))*textures::CARD_TEXTURE_SIZE + 74});
//                        currentCardPtr->mSprite.setPosition(cardSpritePos);
//                        mBoard.addCard(cardPos, *currentCardPtr);
//                        endOfState = true;
//                    }
//                }
//                else {
//                    endOfState = true;
//                }
//                break;
//            }
//            case  sf::Event::KeyPressed :{
//                if(currentState == State::CARDPLACEMENT) {
//                    if (event.key.code == sf::Keyboard::A) {
//                        currentCardPtr->rotateLeft();
//                    }
//
//                    if (event.key.code == sf::Keyboard::D) {
//                        currentCardPtr->rotateRight();
//                    }
//                }
//
//                break;
//            }
//            default :
//                break;
//        }
   }
}

void Game::update() {
}

void Game::render() {
if(currentState == State::CARDPLACEMENT) {
    mGameRenderPtr->render_with_card(currentCardPtr);
}
else {
    mGameRenderPtr->render();
}
}

void Game::change_state() {
    switch (currentState) {
        case State::DEFAULT:{
            currentPlayerIndex= (currentPlayerIndex++) % numberOfPlayers;
            currentPlayerPtr = &mPlayers[currentPlayerIndex];
            currentState = State::CARDPLACEMENT;
            endOfState = false;
            break;
        }
        case State::CARDPLACEMENT: {
            //currentState = State::UNITPLACEMENT;
            currentState = State::DEFAULT;
            endOfState = false;
            break;
        }
        case State::UNITPLACEMENT: {
            currentState = State::DEFAULT;
            endOfState = false;
            break;
        }
    }
}

void Game::execute_unitPlacement() {
    //TODO
}


} // namespace carcassonne_game