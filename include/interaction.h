#ifndef INTERACTION_H_
#define INTERACTION_H_

#include "game_view.h"
#include "game_render.h"

namespace interaction {

struct result {
    sf::Vector2i tile_coordinates = {-1,-1};
    int card_rotation =  0;
};

struct defaultInteraction {
    explicit defaultInteraction(game_view::GameRender *render) : mRender(render) {};

    virtual result handleEvent(sf::Event &event, bool &endOfState, bool &chat);
    void defaultInterfaceInteraction(sf::Event &event, bool &chat);

    virtual ~defaultInteraction() = default;
protected:
    game_view::GameRender *mRender;
};

struct cardPlacementInteraction : public defaultInteraction {
    explicit cardPlacementInteraction(game_view::GameRender *render)
        : defaultInteraction(render){};
    result handleEvent(sf::Event &event, bool &endOfState, bool &chat) override;
};

struct unitPlacementInteraction : public defaultInteraction {
    explicit unitPlacementInteraction(game_view::GameRender *render)
        : defaultInteraction(render){};
    result handleEvent(sf::Event &event, bool &endOfState, bool &chat) override;
};

struct chatInteraction {
    explicit chatInteraction(game_view::GameRender *render): mRender(render){}
    std::string handleEvent(sf::Event &event, bool &endOfState, bool &chat);
private:
    std::string message;
    game_view::GameRender *mRender;
};

}  // namespace interaction

#endif  // INTERACTION_H_