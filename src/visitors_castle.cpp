#include "visitors_castle.h"

namespace visitors{

void visitors::CastleVisitor::visit() {
    clear_marked();
    for (auto &tile : boardPtr->getTypeMap()[Type::CASTLE]){
        if(!marked[tile.position]){
            int numberOfCards = dfs(tile);
            if(numberOfCards) {
                set_score(numberOfCards);
                for(auto &x: units) {
                    for(auto &unit : x.second) {
                        unit->tile->unit = nullptr;
                        unit->tile = nullptr;
                    }
                }
            }
            clear_units();
            cardsID.clear();
        }
    }
}
int CastleVisitor::dfs(Tile &tile) {
    if(tile.type != game_model::Type::CASTLE && tile.type != game_model::Type::CASTLEWITHSHIELD || marked[tile.position]) {
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

void CastleVisitor::set_score(int numberOfCards) {
    std::pair<int, Color> max = {0, RED};
    for(auto &x: units) {
        if(x.second.size() > max.first) {
            max = {x.second.size(), x.first};
        }
    }
    if (max.first != 0) {
        units[max.second][0]->owner->score+= 2*numberOfCards;
    }
}

} // namespace visitors