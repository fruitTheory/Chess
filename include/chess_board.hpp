#pragma once

#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"

extern const std::pair<int, int> square_map[8][8];

class Chessboard{
private:
    const sf::Color dark_square_color;
    const sf::Color light_square_color;
    const sf::Color highlight_color;
    const sf::Vector2f board_square_size;

public:
    Chessboard();
    void create(sf::RenderWindow& window);
    void create_notation_helper(sf::RenderWindow& window);
};