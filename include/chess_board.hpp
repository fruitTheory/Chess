#pragma once

#include "SFML/Graphics.hpp"
#include "chess_pieces.hpp"
#include <utility>

extern const std::pair<int, int> square_map[8][8];

class ChessPieces;

class Chessboard{
private:
    const sf::Color dark_square_color;
    const sf::Color light_square_color;
    const sf::Color highlight_color;
    const sf::Vector2f board_square_size;

public:
    Chessboard():
    dark_square_color(0,45,85,255),
    light_square_color(185,195,205,255),
    board_square_size(96.f, 96.f) {}

    void create(sf::RenderWindow& window);
    void create_notation_helper(sf::RenderWindow& window);
    void reset_board(sf::RenderWindow& window, Chessboard& board, std::vector<ChessPieces>& pieces);
    float get_square_size(){ return board_square_size.x; }
    
};
