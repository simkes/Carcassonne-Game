#include "game_view.h"
#include "view_util.h"

namespace game_view {

using game_model::CARD_DIMENSION;

void TextureHolder::load(textures::ID id, const std::string &filename) {
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
    texture->loadFromFile(filename);
    mTextureMap.insert({id, std::move(texture)});
}

sf::Texture *TextureHolder::get_texture(textures::ID id) {
    return mTextureMap[id].get();
}

CardView::CardView(int texture_id, sf::Vector2f position, int rotation) {
    mSprite.setTexture(*getTextures().get_texture(texture_id < 16 ? textures::ID::CARDS1 : textures::ID::CARDS2));
    int x = game_view::textures::cardCoordinates[texture_id].first;
    int y = game_view::textures::cardCoordinates[texture_id].second;
    mSprite.setTextureRect(sf::IntRect (y*game_view::textures::CARD_TEXTURE_SIZE,
                                       x*game_view::textures::CARD_TEXTURE_SIZE,
                                       game_view::textures::CARD_TEXTURE_SIZE,
                                       game_view::textures::CARD_TEXTURE_SIZE));
    mSprite.setOrigin(textures::CARD_TEXTURE_SIZE/2, textures::CARD_TEXTURE_SIZE/2);
    mSprite.setRotation(90 * rotation);
    mSprite.setPosition(position);
}

void CardView::draw(sf::RenderTarget &target) const {
    target.draw(mSprite);
}

UnitView::UnitView(int color, sf::Vector2f position) {
    game_model::Color col = game_model::colorsVector[color];
    mSprite.setTexture(*getTextures().get_texture(textures::unit_color[col]));
    mSprite.setPosition(position);
    mSprite.setOrigin(textures::UNIT_TEXTURE_SIZE/2, textures::UNIT_TEXTURE_SIZE/2);
}

void UnitView::set_col_and_pos(int color, sf::Vector2f position) {
    game_model::Color col = game_model::colorsVector[color];
    mSprite.setTexture(*getTextures().get_texture(textures::unit_color[col]));
    mSprite.setPosition(position);
}

void UnitView::draw(sf::RenderTarget &target) const {
    target.draw(mSprite);
}

void BoardView::add_card(int texture_id, sf::Vector2f position, int rotation) {
    CardView new_card(texture_id, position, rotation);
    placedCards.push_back(new_card);
}

void BoardView::add_unit(int color, sf::Vector2i position) {
    UnitView new_unit(color, transform_coordinates(position)); //TODO
    units.insert({position,new_unit});
}

void BoardView::delete_unit(sf::Vector2i position) {
    units.erase(position);
}

void BoardView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto& object : placedCards) {
        object.draw(target);
    }
    for (const auto& object :units) {
        object.second.draw(target);
    }
}

void CurrentCardView::set_texture(int texture_id) {
    mSprite.setTexture(*getTextures().get_texture(texture_id < 16 ? textures::ID::CARDS1 : textures::ID::CARDS2));
    int x = game_view::textures::cardCoordinates[texture_id].first;
    int y = game_view::textures::cardCoordinates[texture_id].second;
    mSprite.setTextureRect(sf::IntRect (y*game_view::textures::CARD_TEXTURE_SIZE,
                                       x*game_view::textures::CARD_TEXTURE_SIZE,
                                       game_view::textures::CARD_TEXTURE_SIZE,
                                       game_view::textures::CARD_TEXTURE_SIZE));
}

void CurrentCardView::draw(sf::RenderTarget &target) const {
    target.draw(mSprite);
}
void CurrentCardView::rotate_R() {
    rotation = (rotation + 1) % 4;
    mSprite.setRotation(90 * rotation);
}
void CurrentCardView::rotate_L() {
    for (int i = 0; i < 3; i++) {
        rotate_R();
    }
}

}  // namespace game_view
