#pragma once

#include "SFML/Graphics.hpp"
#include "chess_board.hpp"

enum class Pieces { None = 0, P, B, N, R, Q, K };
extern const std::map<char, Pieces> piece_notation_map;

enum class Letters { a = 1, b, c, d, e, f, g, h };
extern const std::map<char, Letters> letter_notation_map;

extern int piece_map[8][8];

void print_piece_map();
std::string get_user_input();

// Class for all chess pieces - uses shapes can use texture later
class ChessPieces{
    
private:
    sf::CircleShape null_shape;
    sf::CircleShape pawn_shape;
    sf::CircleShape bishop_shape;
    sf::CircleShape knight_shape;
    sf::CircleShape rook_shape; 
    sf::CircleShape king_shape; 
    sf::CircleShape queen_shape;
    int object_id; // generally linked with piece_id
    int color_id; // 0 black 1 white
    int has_moved;

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
    enum class PLAYER { BLACK = 0, WHITE = 1};

    void create_chess_pieces(std::vector<ChessPieces>& pieces);
    void set_piece_colors(std::vector<ChessPieces>& pieces);
    void place_pieces(std::vector<ChessPieces>& pieces);
    void draw_pieces(sf::RenderWindow& window, std::vector<ChessPieces>& pieces);
    void update_pieces(sf::RenderWindow& window, Chessboard& board, std::vector<ChessPieces>& pieces);

    Move_data get_move_input(sf::RenderWindow& window, Chessboard& board, ChessPieces& chess_pieces, std::vector<ChessPieces>& pieces);
    bool move_piece(sf::RenderWindow& window, Chessboard& board, ChessPieces& chess_pieces, std::vector<ChessPieces>& pieces);

    void Set_Piece_ID(int ID);
    int Get_Piece_ID();
    void Set_Color_ID(int ID);
    int Get_Color_ID();
    void Set_Has_Moved(int ID);
    int Get_Has_Moved();
    Pieces get_piece_type();

    Move_data convert_move(const Move_data& move, std::vector<ChessPieces>& pieces);
    bool check_move_validity(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces);
    void check_valid_squares(const Move_data& move_start, const Move_data& move_end);
    bool check_attack(const Move_data& move_start, const Move_data& move_end);

};

class Pawn : public ChessPieces{

    private:

    public:
        bool valid_move(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces);
};

/*
Piece value:
Pawn	1
Knight	3
Bishop	3
Rook	5
Queen	9
*/