#include "server.h"

namespace carcassonne_game::game_server {

void ServerGame::init_players(
    const std::vector<Player> &players) {
    numberOfPlayers = players.size();
    mPlayers.reserve(players.size());
    for (const auto &p : players) {
        mPlayers.emplace_back(p.get_index(), p.name, p.color);
    }
}

ServerGame::ServerGame(unsigned short port) : mServer(port) {
    placedCards.reserve(100);
    init_visitors();
    mCardDeck.init();
    currentState = State::CARDPLACEMENT;
}

void ServerGame::run() {
    std::vector<Player> play;
    mServer.waitConnections(play);
    init_players(play);
    mServer.startGame(mPlayers);
    place_first_card();
    while (!gameOver) {
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
        while (currentState == State::UNITPLACEMENT) {
            if(mPlayers[currentPlayerIndex].get_unit()) {
                sf::Vector2i view_coords =
                    mServer.getUnitPlacement(currentPlayerIndex);
                auto coords = game_view::to_board_tiles(view_coords);
                if(view_coords.x == -1) {
                    mServer.unitTurnDone(view_coords, -1);
                    change_state();
                } else if (mBoard.getTiles()[coords].card && !mBoard.getTiles()[coords].unit) {
                    Unit *unit = mPlayers[currentPlayerIndex].get_unit();
                    mBoard.getTiles()[coords].unit = unit;
                    unit->tile = &mBoard.getTiles()[coords];
                    mServer.unitTurnDone(view_coords, static_cast<int>(unit->owner->color)); //T ODO: check
                    change_state();
                }
            } else {
                change_state();
            }

        }
        update();
        change_state();
    }
    mServer.finishGame();
}

void ServerGame::change_state() {
    switch (currentState) {
        case State::DEFAULT: {
            currentPlayerIndex = (currentPlayerIndex + 1) % numberOfPlayers;
            currentState = State::CARDPLACEMENT;
            break;
        }
        case State::CARDPLACEMENT: {
            currentState = State::UNITPLACEMENT;
            break;
        }
        case State::UNITPLACEMENT: {
            currentState = State::DEFAULT;
            break;
        }
    }
}

void ServerGame::update() {
    std::vector<sf::Vector2i> deleted_units;
    for (int i = 0; i < 3; i++) {  // FieldVisitor goes in the end
        std::vector<sf::Vector2i> result = mVisitors[i]->visit();
        deleted_units.insert(std::end(deleted_units), std::begin(result), std::end(result)); // TODO: check
    }
    std::vector<std::pair<std::string, int>> players_score;
    for(const auto & pl : mPlayers){
        players_score.emplace_back(pl.name, pl.score);
    }
    mServer.update(players_score, deleted_units);
}

void ServerGame::place_first_card() {
    set_currentCard();
    sf::Vector2i pos(102, 102);
    mBoard.addCard(pos, *currentCardPtr);
    mServer.cardTurnDone(*currentCardPtr);
    update();
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