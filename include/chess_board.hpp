#pragma once

#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"

class Chessboard{
private:
    const sf::Color base_color;
    const sf::Color square_color;
    const sf::Color highlight_color;
    const sf::Vector2f board_square_size;

public:
    Chessboard();
    void create(ChessboardWindow& window);
};