#include "visitors_monastery.h"

namespace visitors{

std::vector<sf::Vector2i> visitors::MonasteryVisitor::visit() {
    std::vector<sf::Vector2i> deleted_units;
    for (auto &tile_pos : boardPtr->getTypeMap()[Type::MONASTERY]){
        Tile &tl = boardPtr->getTiles()[tile_pos];
        if (tl.unit){
            bool surrounded = true;
            for(const auto &dir : directions) {
                if(boardPtr->getTiles().count({tile_pos.x + dir.x, tile_pos.y + dir.y}) == 0) {
                    surrounded = false;
                    break;
                }
            }
            if (surrounded) {
             deleted_units.push_back(tile_pos);
             tl.unit->owner->score+=9;
             tl.unit->tile = nullptr;
             tl.unit = nullptr;
            }
        }
    }
    return deleted_units;
}

} // namespace visitors