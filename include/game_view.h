#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include <string>
#include "game_board.h"
#include "view_util.h"
#include "game_player.h"

namespace game_view {

struct TextureHolder {
    void load(textures::ID, const std::string &filename);

    sf::Texture *get_texture(textures::ID);

private:
    std::map<textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

inline TextureHolder &getTextures(){
    static TextureHolder Textures;
    return Textures;
}

inline sf::Font &getFont(){
    static sf::Font font;
    return font; //не знаю обязательно ли здесь было так делать, на всякий
}

struct BoardView : public sf::Drawable {
    //c-tor
    BoardView() = default;
    explicit BoardView(game_model::Board *Board) : mBoard(Board) {};

    void setBoard(game_model::Board *board) {
        mBoard = board;
    }

    sf::View &getView() {
        return mView;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    game_model::Board *mBoard = nullptr;
    sf::View mView;
};

struct CardView : public sf::Drawable, public sf::Transformable {
    explicit CardView(game_model::Card &card, const sf::Texture &card_texture);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite mSprite;
};

struct currentCardView : public sf::Drawable, public sf::Transformable {
    explicit currentCardView(game_model::Card &card, const sf::Texture &card_texture);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite mSprite;
};

struct UnitView : public sf::Drawable, public sf::Transformable {
    explicit UnitView(const game_model::Unit &unit, const sf::Texture &unit_texture);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Sprite mSprite;
};

}  // namespace game_view

#endif  // GAME_VIEW_H_
