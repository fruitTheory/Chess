#pragma once

#include "SFML/Graphics.hpp"
#include "chess_board.hpp"

enum class Pieces { None = 0, P, B, N, R, Q, K };
extern const std::map<char, Pieces> piece_notation_map;

enum class Letters { a = 1, b, c, d, e, f, g, h };
extern const std::map<char, Letters> letter_notation_map;

extern int piece_map[8][8];

std::string get_user_input();

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
    int object_id; // interchangeable with piece_id
    int color_id; // 0 black 1 white 

public:

    ChessPieces();
    
    struct Move_data {
        Pieces piece_type;
        int letter;
        int number;
        int color;
        int piece_id;
    };

    struct Move {
        Move_data start;
        Move_data end;
    };

    // enum class POS { START = 0, END = 1};
    // enum class PLAYER { BLACK = 0, WHITE = 1};

    void create_chess_pieces(std::vector<ChessPieces>& pieces);
    void set_piece_colors(std::vector<ChessPieces>& pieces);
    void place_pieces(std::vector<ChessPieces>& pieces);
    void draw_pieces(sf::RenderWindow& window, std::vector<ChessPieces>& pieces);
    void update_pieces(sf::RenderWindow& window, Chessboard& board, std::vector<ChessPieces>& pieces);

    Move_data get_move_input(sf::RenderWindow& window, Chessboard& board, ChessPieces& chess_pieces, std::vector<ChessPieces> pieces);
    bool move_piece(sf::RenderWindow& window, Chessboard& board, ChessPieces& chess_pieces, std::vector<ChessPieces> pieces);

    void Set_Piece_ID(int ID);
    int Get_Piece_ID();
    void Set_Color_ID(int ID);
    int Get_Color_ID();

    Pieces get_piece_type();
    Move_data convert_move(Move_data move, std::vector<ChessPieces> pieces);

};

class Pawn{

    private:

    public:
        ChessPieces pawn;
        bool valid_move();
};

/*
Piece value:
Pawn	1
Knight	3
Bishop	3
Rook	5
Queen	9
*/