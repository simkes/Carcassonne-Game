#include "game_view.h"
#include "view_util.h"

namespace game_view {

using game_model::CARD_DIMENSION;

void TextureHolder::load(int id, const std::string &filename) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(filename);
    mTextureMap.insert({id, std::move(texture)});
}

void TextureHolder::load(int id, const std::string &filename, int rectLeft, int rectTop, int rectWidth, int rectHeight) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(filename,sf::IntRect(rectLeft, rectTop, rectWidth, rectHeight));
    mTextureMap.insert({id, std::move(texture)});
}

sf::Texture *TextureHolder::get_texture(int id) {
    return mTextureMap[id].get();
}

void BoardView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto object : mBoard.getTiles()) {
        if (object.first.x % CARD_DIMENSION == CARD_DIMENSION / 2 &&
            object.first.y == CARD_DIMENSION / 2) {
            CardView(*object.second->card,
                     *Textures.get_texture(object.second->card->textureId))
                .draw(target, states);
        }
    }

    for (auto object : mBoard.getTiles()) {
        if (object.second->unit != nullptr) {
            UnitView(*object.second->unit, *Textures.get_texture(unit_color[object.second->unit->owner->color]));
        }
    }
}

void CardView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

CardView::CardView(const game_model::Card &card,
                   const sf::Texture &card_texture) {
    mSprite.setTexture(card_texture);
    mSprite.setRotation(static_cast<float>(90 * card.rotation));
    mSprite.setPosition(transform_coordinates(card.getTile(0, 0)->position));
}

UnitView::UnitView(const game_model::Unit &unit,
                   const sf::Texture &unit_texture) {
    mSprite.setTexture(unit_texture);
    mSprite.setPosition(transform_coordinates(unit.tile->position));
}

void UnitView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

}  // namespace game_view
