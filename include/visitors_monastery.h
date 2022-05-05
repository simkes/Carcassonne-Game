#ifndef VISITORS_MONASTERY_H_
#define VISITORS_MONASTERY_H_
#include "visitors_abstract.h"

namespace visitors{

class MonasteryVisitor final : public AbstractVisitor {
public:
    void visit(sf::Vector2i pos) final;
private:
    const std::vector<sf::Vector2i> directions { {CARD_DIMENSION,0}, {0, CARD_DIMENSION},
                                               {-CARD_DIMENSION,0}, {0, -CARD_DIMENSION},
                                               {CARD_DIMENSION,CARD_DIMENSION}, {-CARD_DIMENSION, CARD_DIMENSION},
                                               {CARD_DIMENSION,-CARD_DIMENSION}, {-CARD_DIMENSION, -CARD_DIMENSION} };
};

} // namespace visitors

#endif // VISITORS_MONASTERY_H_