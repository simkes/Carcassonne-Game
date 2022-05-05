#include "visitors_field.h"

namespace visitors{

void visitors::FieldVisitor::visit() {
    for (auto &tile : boardPtr->getTypeMap()[Type::FIELD]){
        if(!marked[tile.position]){
            int numberOfCastles = dfs_in_field(tile);
            set_score(numberOfCastles);
            for(auto &x: units) {
                for(auto &unit : x.second) {
                    unit->tile->unit = nullptr;
                    unit->tile = nullptr;
                }
            }
            clear_units();
            clear_markedCastles();
        }
    }
}

int FieldVisitor::dfs_in_field(Tile &tile){
    if(tile.type != game_model::Type::FIELD || marked[tile.position]) {
        return 0;
    }
    int adjacentCastles = 0;
    marked[tile.position] = 1;
    Unit *unitPtr = tile.unit;
    if(unitPtr){
        units[unitPtr->owner->color].push_back(unitPtr);
    }

    for (const auto &[dx,dy] : directions){
        sf::Vector2i nextPos = {tile.position.x + dx, tile.position.y + dy};
        if(boardPtr->getTiles().count(nextPos) != 0) {
            if(boardPtr->getTiles()[nextPos].type == game_model::Type::CASTLE) {
                adjacentCastles += (int)dfs_in_castle(boardPtr->getTiles()[nextPos]);
            } else {
                adjacentCastles += dfs_in_field(boardPtr->getTiles()[nextPos]);
            }
        }
    }

    return adjacentCastles;
}

bool FieldVisitor::dfs_in_castle(Tile &tile) {
    if(tile.type != game_model::Type::CASTLE && tile.type != game_model::Type::CASTLEWITHSHIELD || markedCastles[tile.position]) {
        return true;
    }
    markedCastles[tile.position] = 1;
    bool completed = true;

    for (const auto &[dx,dy] : directions){
        sf::Vector2i nextPos = {tile.position.x + dx, tile.position.y + dy};
        if(boardPtr->getTiles().count(nextPos) == 0) {
            completed = false;
        }
        else {
            completed = dfs_in_castle(boardPtr->getTiles()[nextPos]);
        }
    }

    return completed;
}

void FieldVisitor::set_score(int numberOfCastles) {
    std::pair<int, Color> max = {0, RED};
    for(auto &x: units) {
        if(x.second.size() > max.first) {
            max = {x.second.size(), x.first};
        }
    }
    if (max.first != 0) {
        units[max.second][0]->owner->score+= 3*numberOfCastles;
    }
}


} // namespace visitors