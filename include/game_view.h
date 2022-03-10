#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include <map>
#include "game_board.h"

namespace game_view {

namespace textures {

enum class ID { Card };

} // namespace textures

struct TextureHolder {
    void load(textures::ID id, const std::string &filename);

private:
    std::map<textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

struct BoardView : public sf::Drawable {
    sf::View & getView() {
        return mView;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    const game_model::Board &mBoard;
    sf::View mView;
};

struct CardView : public sf::Drawable, public sf::Transformable {
    explicit CardView(const game_model::Card &card);
};

} // namespace game_view

#endif // GAME_VIEW_H_
