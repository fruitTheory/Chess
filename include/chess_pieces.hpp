#pragma once

#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"
#include "chess_board.hpp"

enum class PieceType {
    PAWN = 1, 
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum Letters { a = 1, b, c, d, e, f, g, h };

enum Pieces { N = 1, B, R, Q, K };

// Class for all chess pieces - uses shapes can use texture later
class ChessPieces{
private:
    sf::CircleShape null;
    sf::CircleShape pawn;
    sf::CircleShape knight;
    sf::CircleShape bishop;
    sf::CircleShape rook; 
    sf::CircleShape king; 
    sf::CircleShape queen;
public:

    struct Move {
        int pieceType;
        int letter;
        int number;
    };
    ChessPieces();
    sf::CircleShape& get_piece_basic(int piece_type);
    void draw_pieces(ChessboardWindow& window);
    Move get_piece();
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

 bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);