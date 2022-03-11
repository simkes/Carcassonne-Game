#include "game_view.h"

namespace game_view {

using game_model::CARD_DIMENSION;

    void TextureHolder::load(textures::ID id, const std::string &filename) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(filename);
    mTextureMap.insert({id, std::move(texture)});
}

void BoardView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto object : mBoard.getTiles()) {
        if (object.first.x % CARD_DIMENSION == CARD_DIMENSION / 2 &&
            object.first.y == CARD_DIMENSION / 2) {
            CardView(object.second->card).draw(target, states);
        }
    }
}

void CardView::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}

CardView::CardView(const game_model::Card &card) {
    mSprite.setTexture(*(texture_holder->get_texture(card.texture_id)));
    mSprite.setRotation(static_cast<float>(90 * card.rotation));
    //mSprite.setPosition(card.getTile(0, 0)->position)
}

}  // namespace game_view