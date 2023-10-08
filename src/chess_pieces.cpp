#include "chess_pieces.hpp"

ChessPieces::ChessPieces():
pawn(48.f, 3),
rook(48.f, 4),
king(48.f, 8),
queen(48.f, 100)
{

}

// 48 unit size piece
sf::CircleShape& ChessPieces::get_piece(PieceType piece){
    switch (piece)
    {
    case PieceType::PAWN: return pawn; break;
    case PieceType::ROOK: return rook; break;
    case PieceType::KING: return king; break;
    case PieceType::QUEEN: return queen; break;
    default:
        puts("Pick a chess piece");
        break;
    }
}