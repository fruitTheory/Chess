#pragma once

#include "SFML/Graphics.hpp"

enum class PieceType {
    PAWN, ROOK, KING, QUEEN
};

// Class for all chess pieces - uses shapes can use texture later
class ChessPieces{
private:
    sf::CircleShape pawn;
    sf::CircleShape rook; 
    sf::CircleShape king; 
    sf::CircleShape queen;
public:
    ChessPieces();
    sf::CircleShape& get_piece(PieceType type);
};

/*
Piece value:
Pawn	1
Knight	3
Bishop	3
Rook	5
Queen	9
*/