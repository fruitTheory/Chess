#pragma once

#include "SFML/Graphics.hpp"
#include "chess_window.hpp"

enum class PieceType {
    PAWN = 1, 
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

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
    ChessPieces();
    sf::CircleShape& get_piece(int piece_type);
    void initialize_piece_position(ChessboardWindow& window);
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