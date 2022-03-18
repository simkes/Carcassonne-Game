#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "game_board.h"
#include "game_card.h"
#include "view_util.h"
#include "game_player.h"

namespace game_view {

struct TextureHolder {
    void load(textures::ID id, const std::string &filename);
    void load(textures::ID id, const std::string &filename, int rectLeft, int rectTop, int rectWidth, int rectHeight );

    sf::Texture *get_texture(textures::ID id);

private:
    std::map<textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

static TextureHolder Textures;

struct BoardView : public sf::Drawable {
    //c-tor
    BoardView(game_model::Board &Board) : mBoard(Board) {};

    sf::View &getView() {
        return mView;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    game_model::Board &mBoard;
    sf::View mView;
};

struct CardView : public sf::Drawable, public sf::Transformable {
    explicit CardView(const game_model::Card &card, const sf::Texture &card_texture);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite mSprite;
};

std::map<game_model::Color, textures::ID>unit_color;

struct UnitView : public sf::Drawable, public sf::Transformable {
    explicit UnitView(const game_model::Unit &unit, const sf::Texture &unit_texture);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite mSprite;
};

}  // namespace game_view

#endif  // GAME_VIEW_H_
