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
    return font;
}

struct CardView {
    explicit CardView(int texture_id, sf::Vector2f position, int rotation);
    void draw(sf::RenderTarget &target) const;
private:
    sf::Sprite mSprite;
};

struct UnitView {
    UnitView() = default;
    explicit UnitView(int color, sf::Vector2f position);
    void set_col_and_pos(int color, sf::Vector2f position);
    void draw(sf::RenderTarget &target) const;
private:
    sf::Sprite mSprite;
};

struct BoardView : public sf::Drawable {
    //c-tor
    BoardView() {
        mView.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        mView.setCenter(3074, 3074);
    }
    sf::View &getView() {
        return mView;
    }

    void add_card(int texture_id, sf::Vector2f position, int rotation);
    void add_unit(int color, sf::Vector2i position);
    void delete_unit(sf::Vector2i position);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::vector<CardView> placedCards;
    std::map<sf::Vector2i, UnitView,game_model::Comp> units; // made map as some units will be deleted
                                                             // key = tile pos on board
    sf::View mView;
};

struct CurrentCardView {
    CurrentCardView() {
        mSprite.setPosition({115, 205});
        mSprite.setOrigin(textures::CARD_TEXTURE_SIZE/2, textures::CARD_TEXTURE_SIZE/2);
    }
    void set_texture(int texture_id);
    void rotate_R();
    void rotate_L();
    int get_rotation(){
        return rotation;
    }
    void draw(sf::RenderTarget &target) const;
private:
    sf::Sprite mSprite;
    int rotation = 0;
};

}  // namespace game_view

#endif  // GAME_VIEW_H_
