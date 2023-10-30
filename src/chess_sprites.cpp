#include "chess_sprites.hpp"

// temp sprite setup, simple processing 
sf::Sprite setup_sprite(sf::RenderWindow& window){
        
    sf::Vector2f halve(0.5f, 0.5f);
    sf::Color bg(185,195,205,255);

    sf::Texture texture;
    if(!texture.loadFromFile("./img/white_queen.png")) { puts("Error"); }
    sf::Sprite sprite(texture);

    sprite.setTexture(texture);
    sprite.setPosition(50, 50);
    sf::Vector2u originalSize = sprite.getTexture()->getSize();

    float scaleX = 48.0f / originalSize.x;
    float scaleY = 48.0f / originalSize.y;
    sprite.setScale(scaleX, scaleY);

    window.clear(bg);
    window.draw(sprite);
    window.display();

    return sprite;
}