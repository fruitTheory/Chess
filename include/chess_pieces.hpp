#pragma once

#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"
#include "chess_board.hpp"

enum class Pieces { P = 1, B, N, R, Q, K };
extern const std::map<char, Pieces> piece_notation_map;

enum class Letters { a = 1, b, c, d, e, f, g, h };
extern const std::map<char, Letters> letter_notation_map;

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
    sf::CircleShape piece_type;
    int object_id;

public:

    ChessPieces();

    struct Selection {
        int piece_type;
        int letter;
        int number;
    };

    void create_chess_pieces(std::vector<ChessPieces>& chess_pieces);
    void move_piece_colors(std::vector<ChessPieces>& chess_pieces);
    void place_pieces(std::vector<ChessPieces>& chess_pieces);
    void render_pieces(ChessboardWindow& window, std::vector<ChessPieces>& chess_pieces);
    void setup_pieces(ChessboardWindow& window, std::vector<ChessPieces>& chess_pieces);

    Selection select_piece(bool destination);
    void move_piece(ChessboardWindow& window, Chessboard& board);

    void Set_ID(int ID);
    int Get_ID();

    sf::CircleShape get_piece_type();
};

/*
Piece value:
Pawn	1
Knight	3
Bishop	3
Rook	5
Queen	9
*/