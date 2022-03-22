#include "game_board.h"

namespace game_model {

bool Board::canAddCard(sf::Vector2i pos, Card &card) {
    if (pos.x % (CARD_DIMENSION - 1) != 0 ||
        pos.y % (CARD_DIMENSION - 1) != 0) {
        return false;
    }
    // TODO: debug, rewrite simpler
    for (int dy : {0, CARD_DIMENSION - 1}) {
        for (int dx = 0; dx < CARD_DIMENSION; dx++) {
            if (mTiles[sf::Vector2i{pos.x + dx, pos.y + dy}].type !=
                card.getTile(dx, dy).type) {
                return false;
            }
        }
    }
    for (auto dx : {0, CARD_DIMENSION - 1}) {
        for (int dy = 0; dx < CARD_DIMENSION; dx++) {
            if (mTiles[sf::Vector2i{pos.x + dx, pos.y + dy}].type !=
                card.getTile(dx, dy).type) {
                return false;
            }
        }
    }
    return true;
}

const std::vector<sf::Vector2i> cardBounds{ {CARD_DIMENSION - 1,0}, {0, CARD_DIMENSION - 1},
                                           {-CARD_DIMENSION + 1,0}, {0, -CARD_DIMENSION + 1}}; //TODO: rename

const std::vector<std::vector<Tile>> &Board::addCard(sf::Vector2i pos,
                                                      Card &card) {

    for (const auto &position : cardBounds){
        sf::Vector2i newEmptyPos = {pos.x + position.x, pos.y + position.y};
        sf::Vector2i cardCenterPos = {newEmptyPos.x + CARD_DIMENSION/2, newEmptyPos.y + CARD_DIMENSION/2};
        if(mTiles.count(cardCenterPos) == 0){
            emptyPositions.insert(newEmptyPos);
        }
    }

    for (int dx = 0; dx < CARD_DIMENSION; dx++) {
        for (int dy = 0; dy < CARD_DIMENSION; dy++) {
            //if (mTiles[{pos.x + dx, pos.y + dy}] == nullptr) { // TODO: handle tiles belonging to 2 cards
                card.getTile(dx,dy).position = {pos.x+dx, pos.y+dy};
                mTiles.insert({{pos.x + dx, pos.y + dy}, card.getTile(dx, dy)});
                
           // }
        }
    }

    return card.getTiles();
}
sf::Vector2i Board::getEmptyPosition(sf::Vector2i position) {
    int x = position.x;
    int y = position.y;
    sf::Vector2i result;
    int minDistSq = INT32_MAX;
    for(const auto & pos : emptyPositions){
        int screenPosX = (pos.x /(CARD_DIMENSION-1))*game_view::textures::CARD_TEXTURE_SIZE + game_view::textures::CARD_TEXTURE_SIZE/2;
        int screenPosY = (pos.y/(CARD_DIMENSION-1))*game_view::textures::CARD_TEXTURE_SIZE + game_view::textures::CARD_TEXTURE_SIZE/2;
        int distSq = (screenPosX - x)*(screenPosX - x) + (screenPosY - y)*(screenPosY - y);
        if( distSq < minDistSq ){
            minDistSq = distSq;
            result = {pos.x, pos.y};
        }
    }
    emptyPositions.erase(result);
    return result;
}

}  // namespace game_model
