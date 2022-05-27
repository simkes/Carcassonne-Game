#include "visitors_monastery.h"

namespace visitors{

std::vector<sf::Vector2i> visitors::MonasteryVisitor::visit() {
    std::vector<sf::Vector2i> deleted_units;
    for (auto &tile : boardPtr->getTypeMap()[Type::MONASTERY]){
        if (tile.unit){
            sf::Vector2i tilePos = tile.position;
            bool surrounded = true;
            for(const auto &dir : directions) {
                if(boardPtr->getTiles().count({tilePos.x + dir.x, tilePos.y + dir.y}) == 0) {
                    surrounded = false;
                    break;
                }
            }
            if (surrounded) {
             deleted_units.push_back(tile.position);
             tile.unit->owner->score+=9;
             tile.unit->tile = nullptr;
             tile.unit = nullptr;
            }
        }
    }
    return deleted_units;
}

} // namespace visitors