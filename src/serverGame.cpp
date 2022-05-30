#include "server.h"

namespace carcassonne_game::game_server {

void ServerGame::init_players(
    const std::vector<Player> &players) {
    numberOfPlayers = players.size();
    for (const auto &p : players) {
        mPlayers.emplace_back(p.get_index(), p.name, p.color);
    }
}

ServerGame::ServerGame(unsigned short port) : mServer(port) {
    placedCards.reserve(100);
    init_visitors();
    currentPlayerPtr = &mPlayers[currentPlayerIndex];
    place_first_card();
    // currentState = State::UNITPLACEMENT;
    currentState = State::CARDPLACEMENT;
    // currentPlayerPtr = &mPlayers[currentPlayerIndex];
    mCardDeck.init();
}

void ServerGame::run() {
    std::vector<Player> play;
    play = mServer.waitConnections(play);
    init_players(play);
    mServer.startGame(mPlayers);
    place_first_card();
    while (!gameOver) {
        if (currentState == State::CARDPLACEMENT) {
            set_currentCard();
            mServer.newTurn(currentPlayerIndex, *currentCardPtr);
            while (currentState == State::CARDPLACEMENT) {
                std::pair<sf::Vector2i, int> coords =
                    mServer.getCardPlacement(currentPlayerIndex);
                currentCardPtr->set_rotation(coords.second);
                if (mBoard.canAddCard(coords.first, *currentCardPtr)) {
                    mBoard.addCard(coords.first, *currentCardPtr);
                    mServer.cardTurnDone(*currentCardPtr);
                    change_state();
                }
            }
        }
        if (currentState == State::UNITPLACEMENT) {
            if(mPlayers[currentPlayerIndex].get_unit()) {
                sf::Vector2i coords =
                    mServer.getUnitPlacement(currentPlayerIndex);
                if(coords.x != -1) {
                    Unit *unit = mPlayers[currentPlayerIndex].get_unit();
                    mBoard.getTiles()[coords].unit = unit;
                    unit->tile = &mBoard.getTiles()[coords];
                    mServer.unitTurnDone(coords, static_cast<int>(unit->owner->color)); //TODO: check
                }
            }
            change_state();
        }
        currentPlayerIndex = (currentPlayerIndex + 1) % mPlayers.size();
        currentPlayerPtr = &mPlayers[currentPlayerIndex];
        update();
        change_state();
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
            currentState = State::UNITPLACEMENT;
            //currentState = State::DEFAULT;
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
    mServer.cardTurnDone(*currentCardPtr);
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