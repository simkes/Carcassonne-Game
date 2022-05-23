#include "server.h"

namespace carcassonne_game::game_server {

void ServerGame::init_players(
    std::vector<std::pair<sf::String, game_model::Color>> &players) {
    numberOfPlayers = players.size();
    for (const auto &p : players) {
        mPlayers.emplace_back(p.first, p.second);
    }
}

ServerGame::ServerGame(std::vector<std::pair<sf::String, game_model::Color>> players) : numberOfPlayers(players.size()) {
    placedCards.reserve(100);
    init_players(players);
    init_visitors();
    currentPlayerPtr = &mPlayers[currentPlayerIndex];
    place_first_card();
    // currentState = State::UNITPLACEMENT;
    currentState = State::CARDPLACEMENT;
    // currentPlayerPtr = &mPlayers[currentPlayerIndex];
}

void ServerGame::run() {

    mServer.startGame(mPlayers);
    while (!gameOver) {
        if (currentState == State::CARDPLACEMENT) {
            set_currentCard();
            while (currentState == State::CARDPLACEMENT) {
                sf::Vector2i coords =
                    mServer.getCardPlacement(currentPlayerIndex);
                if (mBoard.canAddCard(coords, *currentCardPtr)) {
                    mBoard.addCard(coords, *currentCardPtr);
                    mServer.newTurn(currentPlayerIndex, *currentCardPtr);
                    change_state();
                }
            }
        }
        if (currentState == State::UNITPLACEMENT) {
            // t ODO
            change_state();
        }
        currentPlayerIndex = (currentPlayerIndex + 1) % mPlayers.size();
        currentPlayerPtr = &mPlayers[currentPlayerIndex];
        update();
    }
    mServer.finishGame();
}

void ServerGame::change_state() {
    switch (currentState) {
        case State::DEFAULT: {
            currentPlayerIndex = (currentPlayerIndex + 1) % numberOfPlayers;
            currentPlayerPtr = &mPlayers[currentPlayerIndex];
            currentState = State::CARDPLACEMENT;
            endOfState = false;
            break;
        }
        case State::CARDPLACEMENT: {
            // currentState = State::UNITPLACEMENT;
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

void ServerGame::update() {
    for (int i = 0; i < 3; i++) {  // FieldVisitor goes in the end
        mVisitors[i]->visit();
    }
}

void ServerGame::place_first_card() {
    set_currentCard();
    sf::Vector2i pos(102, 102);
    mBoard.addCard(pos, *currentCardPtr);
}

void ServerGame::set_currentCard() {
    if (mCardDeck.empty()) {
        gameOver = true;  // T ODO: make end of game with score counted
        return;
    }
    Card newCard = mCardDeck.get_card();
    newCard.id = static_cast<int>(placedCards.size());
    placedCards.push_back(newCard);
    placedCards.back().setTiles();
    currentCardPtr = &placedCards.back();
}

void ServerGame::init_visitors() {
    mVisitors.emplace_back(std::make_unique<visitors::RoadVisitor>(&mBoard));
    mVisitors.emplace_back(std::make_unique<visitors::CastleVisitor>(&mBoard));
    mVisitors.emplace_back(
        std::make_unique<visitors::MonasteryVisitor>(&mBoard));
    mVisitors.emplace_back(std::make_unique<visitors::FieldVisitor>(&mBoard));
}


} // namespace carcassonne_game::game_server