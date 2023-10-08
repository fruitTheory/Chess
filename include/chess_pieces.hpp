#pragma once

#include "SFML/Graphics.hpp"

enum class PieceType {
    PAWN, ROOK, KING, QUEEN
};

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