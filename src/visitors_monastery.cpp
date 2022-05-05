#include "visitors_monastery.h"

namespace visitors{

void visitors::MonasteryVisitor::visit(sf::Vector2i pos) {
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
             tile.unit->owner->score+=9;
             tile.unit->tile = nullptr;
             tile.unit = nullptr;
            }
        }
    }
}

} // namespace visitors