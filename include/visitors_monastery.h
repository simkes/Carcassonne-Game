#ifndef VISITORS_MONASTERY_H_
#define VISITORS_MONASTERY_H_
#include "visitors_abstract.h"

namespace visitors{

class MonasteryVisitor final : public AbstractVisitor {
public:
    void visit(sf::Vector2i pos) final;
};

} // namespace visitors

#endif // VISITORS_MONASTERY_H_