#include "visitors_road.h"

namespace visitors{

std::vector<sf::Vector2i> visitors::RoadVisitor::visit() {
    std::vector<sf::Vector2i> deleted_units;
    clear_marked();
    for (auto &tile_pos : boardPtr->getTypeMap()[Type::ROAD]){
        if(!marked[tile_pos]){
            Tile &tl = boardPtr->getTiles()[tile_pos];
            int numberOfCards = dfs(tl);
            if(numberOfCards) {
                set_score(numberOfCards);
                for(auto &x: units) {
                    for(auto &unit : x.second) {
                        deleted_units.push_back(unit->tile->position);
                        unit->tile->unit = nullptr;
                        unit->tile = nullptr;
                    }
                }
            }
            clear_units();
            cardsID.clear();
        }
    }
    return deleted_units;
}
int RoadVisitor::dfs(Tile &tile) {
    if(tile.type != game_model::Type::ROAD || marked[tile.position]) {
        return (int)cardsID.size();
    }
    marked[tile.position] = 1;
    bool completed = true;
    cardsID.insert(tile.cardIDs.first);
    Unit *unitPtr = tile.unit;
    if(unitPtr){
        units[unitPtr->owner->color].push_back(unitPtr);
    }

    for (const auto &[dx,dy] : directions){
        sf::Vector2i nextPos = {tile.position.x + dx, tile.position.y + dy};
        if(boardPtr->getTiles().count(nextPos) == 0) {
            completed = false;
        }
        else {
            if(!dfs(boardPtr->getTiles()[nextPos])) {
                completed = false;
            }
        }
    }

    if(completed) {
        return (int)cardsID.size();
    }
    return 0;
}

void RoadVisitor::set_score(int numberOfCards) {
    for(auto &x: units) {
        if(!x.second.empty()) {
            x.second[0]->owner->score+= numberOfCards;
        }
    }
}

} // namespace visitors