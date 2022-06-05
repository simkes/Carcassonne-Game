#ifndef VISITORS_MONASTERY_H_
#define VISITORS_MONASTERY_H_
#include "visitors_abstract.h"

namespace visitors{

class MonasteryVisitor final : public AbstractVisitor {
public:
    explicit MonasteryVisitor(Board *boardPtr_) : AbstractVisitor(boardPtr_) {}
    std::vector<sf::Vector2i> visit() final;
private:
    const std::vector<sf::Vector2i> directions { {CARD_DIMENSION-1,0}, {0, CARD_DIMENSION-1},
                                               {-CARD_DIMENSION+1,0}, {0, -CARD_DIMENSION+1},
                                               {CARD_DIMENSION-1,CARD_DIMENSION-1}, {-CARD_DIMENSION+1, CARD_DIMENSION-1},
                                               {CARD_DIMENSION-1,-CARD_DIMENSION+1}, {-CARD_DIMENSION+1, -CARD_DIMENSION+1} };
};

} // namespace visitors

#endif // VISITORS_MONASTERY_H_