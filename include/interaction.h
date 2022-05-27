#ifndef INTERACTION_H_
#define INTERACTION_H_

#include "game_view.h"
#include "game_render.h"

namespace interaction {

struct result {
    sf::Vector2i tile_coordinates = {-1,-1};
    int card_rotation =  -1;
};

struct defaultInteraction {
    explicit defaultInteraction(game_view::GameRender *render) : mRender(render) {};

    virtual result handleEvent(sf::Event &event, bool &endOfState);
    void defaultInterfaceInteraction(sf::Event &event);

    virtual ~defaultInteraction() = default;
protected:
    game_view::GameRender *mRender;
};

struct cardPlacementInteraction : public defaultInteraction {
    explicit cardPlacementInteraction(game_view::GameRender *render)
        : defaultInteraction(render){};
    result handleEvent(sf::Event &event, bool &endOfState) override;
};

struct unitPlacementInteraction : public defaultInteraction {
    explicit unitPlacementInteraction(game_view::GameRender *render)
        : defaultInteraction(render){};
    result handleEvent(sf::Event &event, bool &endOfState) override;
};

}  // namespace interaction

#endif  // INTERACTION_H_