#ifndef VISITORS_FIELD_H_
#define VISITORS_FIELD_H_
#include "visitors_abstract.h"

namespace visitors{

class FieldVisitor final : public AbstractVisitor {
public:
    explicit FieldVisitor(Board *boardPtr_) : AbstractVisitor(boardPtr_) {}
    std::vector<sf::Vector2i> visit() final;
private:
    const std::vector<sf::Vector2i> directions { {1,0}, {0, 1}, {-1,0}, {0,-1} };
    std::map <sf::Vector2i , int, Comp> marked;
    std::map <sf::Vector2i , int, Comp> markedCastles;
    std::unordered_map <Color, std::vector<Unit *>> units;

    void clear_markedCastles(){
        for(auto &[pos,flag] : markedCastles) {
            flag = 0;
        }
    }
    void clear_units() {
        for(auto &x: units) {
            x.second.clear();
        }
    }

    bool dfs_in_castle(Tile &tile); //returns true if castle is completed
    int dfs_in_field(Tile &tile); //returns the number of completed castles adjacent to the field
    void set_score(int numberOfCastles);
};

} // namespace visitors

#endif // VISITORS_FIELD_H_