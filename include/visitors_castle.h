#ifndef VISITORS_CASTLE_H_
#define VISITORS_CASTLE_H_
#include "visitors_abstract.h"

namespace visitors{

class CastleVisitor final : public AbstractVisitor { // TODO: handle shield
public:
    void visit(sf::Vector2i pos) final;
private:
    const std::vector<sf::Vector2i> directions { {1,0}, {0, 1}, {-1,0}, {0,-1} };
    std::map <sf::Vector2i , int, Comp> marked;
    std::unordered_map <Color, std::vector<Unit *>> units;
    std::set <int> cardsID;
    void clear_marked(){
        for(auto &[pos,flag] : marked) {
            flag = 0;
        }
    }
    void clear_units() {
        for(auto &x: units) {
            x.second.clear();
        }
    }
    int dfs(Tile &tile); //returns the number of cards belonging to the castle if succeeded, 0  - otherwise
    void set_score(int numberOfCards);
};

} // namespace visitors

#endif // VISITORS_CASTLE_H_