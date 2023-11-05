#pragma once

#include "SFML/Graphics.hpp"
#include "chess_board.hpp"

sf::Vector2i get_mouse_position(sf::RenderWindow& window);
ChessPieces::Move move_from_click(Chessboard& board, sf::Vector2i mouse_position);