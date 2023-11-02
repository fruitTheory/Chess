#include "chess_sprites.hpp"
#include "texture.hpp"

// temp sprite setup, simple processing 
sf::Sprite setup_sprite(sf::RenderWindow& window){
        
    sf::Vector2f halve(0.5f, 0.5f);
    sf::Color bg(185,195,205,255);

    sf::Texture& texture = ChessTexture::default_texture();
    sf::Sprite sprite(texture);

    sprite.setTexture(texture);
    sprite.setPosition(50, 50);
    sf::Vector2u original_size = sprite.getTexture()->getSize();

    float scaleX = 48.0f / original_size.x;
    float scaleY = 48.0f / original_size.y;
    sprite.setScale(scaleX, scaleY);

    window.clear(bg);
    window.draw(sprite);
    window.display();

    return sprite;
}