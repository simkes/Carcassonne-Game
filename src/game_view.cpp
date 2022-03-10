#include "game_view.h"

namespace game_view {

using game_model::CARD_DIMENSION

    void
    TextureHolder::load(textures::ID id, const std::string &filename) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(filename);
    mTextureMap.insert({id, std::move(texture)});
}

void BoardView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto object : mBoard.getTiles()) {
        if (object.first.x % CARD_DIMENSION == CARD_DIMENSION / 2 &&
            object.first.y == CARD_DIMENSION / 2) {
            CardView(object.second.card).draw(target, states);
        }
    }
}

}  // namespace game_view