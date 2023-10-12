#pragma once

#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"
#include "chess_board.hpp"

enum PieceType { PAWN = 1, KNIGHT, BISHOP, ROOK, QUEEN, KING };
enum Pieces { N = 1, B, R, Q, K };

// Class for all chess pieces - uses shapes can use texture later
class ChessPieces{
private:
    sf::CircleShape null;
    sf::CircleShape pawn;
    sf::CircleShape bishop;
    sf::CircleShape knight;
    sf::CircleShape rook; 
    sf::CircleShape king; 
    sf::CircleShape queen;
public:

    struct Move {
        int piece_type;
        int letter;
        int number;
    };
    ChessPieces();
    sf::CircleShape& get_piece_basic(int piece_type);
    void draw_pieces(ChessboardWindow& window);
    Move get_move();
    void set_piece(ChessboardWindow& window, Chessboard& board);

};

/*
Piece value:
Pawn	1
Knight	3
Bishop	3
Rook	5
Queen	9
*/