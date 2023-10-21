#pragma once

#include "SFML/Graphics.hpp"
#include "chess_board.hpp"
#include "chess_pieces.hpp"


void initialize_window(sf::RenderWindow& window);
void initialize_render(sf::RenderWindow& window, Chessboard& board, ChessPieces& chess_pieces, std::vector<ChessPieces> pieces);