#ifndef VISITORS_ABSTRACT_H_
#define VISITORS_ABSTRACT_H_
#include "game_board.h"
#include "game_unit.h"
#include "game_player.h"
#include <unordered_map>

using namespace game_model;

namespace visitors{

class AbstractVisitor {
protected:
    Board *boardPtr;

public:
    explicit AbstractVisitor(Board *boardPtr_) : boardPtr(boardPtr_) {}
    virtual std::vector<sf::Vector2i> visit() = 0;
    // some connectivity ?
    virtual ~AbstractVisitor() = default;
};

} // namespace visitors

#endif // VISITORS_ABSTRACT_H_