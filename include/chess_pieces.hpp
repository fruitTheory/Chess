#pragma once

#include "SFML/Graphics.hpp"
#include "chess_board.hpp"


enum class Pieces { None = 0, P, B, N, R, Q, K };
extern const std::map<char, Pieces> piece_notation_map;
std::ostream& operator<<(std::ostream& os, const Pieces& value);

enum class Letters { a = 1, b, c, d, e, f, g, h };
extern const std::map<char, Letters> letter_notation_map;

enum class Piece_Value { None = 0, Pawn = 1, Knight = 3, Bishop = 3, Rook = 5, Queen = 9 };

enum class DIRECTION;

extern int piece_map[8][8];

class Chessboard;

// Class for all chess pieces - uses smfl shapes - specific piece classes are just for organization
class ChessPieces{
    
private:

    // Piece shapes

    sf::CircleShape null_shape;
    sf::CircleShape pawn_shape;
    sf::CircleShape bishop_shape;
    sf::CircleShape knight_shape;
    sf::CircleShape rook_shape; 
    sf::CircleShape king_shape; 
    sf::CircleShape queen_shape;

    // Piece data

    Piece_Value object_value; // value of piece
    int object_id; // typically linked with piece_id, but more static use case
    int color_id; // 0:black 1:white
    bool has_moved; // if piece has moved

public:

    // Construction
    ChessPieces():
    null_shape(0.f, 0),
    pawn_shape(48.f, 3),
    bishop_shape(48.f, 4),
    knight_shape(48.f, 5),
    rook_shape(48.f, 6),
    king_shape(48.f, 8),
    queen_shape(48.f, 100){}
    
    // General data for active moving pieces
    struct Move_data {
        Pieces piece_type;
        int letter;
        int number;
        int color;
        int piece_id;
    };

    // Completed move containing move data
    struct Move {
        Move_data start;
        Move_data end;
    };

    // Piece creation

    void create_chess_pieces(std::vector<ChessPieces>& pieces);
    void set_piece_colors(std::vector<ChessPieces>& pieces);
    void place_pieces(std::vector<ChessPieces>& pieces);
    void draw_pieces(sf::RenderWindow& window, std::vector<ChessPieces>& pieces);
    void update_pieces(sf::RenderWindow& window, Chessboard& board, std::vector<ChessPieces>& pieces);

 
    // Piece moving

    Move_data convert_move(const Move_data& move, std::vector<ChessPieces>& pieces);
    bool move_piece(sf::RenderWindow& window, Chessboard& board, 
                    std::vector<ChessPieces>& pieces, ChessPieces::Move& move);
    void set_piece(Move move, std::vector<ChessPieces>& pieces);


    // Getters and setters

    void Set_Object_ID(int ID);
    int Get_Object_ID();
    void Set_Color_ID(int ID);
    int Get_Color_ID();
    void Set_Has_Moved(bool moved);
    bool Get_Has_Moved();
    void Set_Object_Value(Pieces type);
    Piece_Value Get_Object_Value();
    Pieces get_piece_type();
    std::string get_piece_type_str(Pieces type);
    std::array<int, 2> get_move_distance(const Move_data& move_start, const Move_data& move_end);
    DIRECTION get_move_direction(const Move_data& move_start, const Move_data& move_end);


    // Checkers 
 
    bool check_attack(const Move_data& move_start, const Move_data& move_end);
    bool check_obstruction(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces);
    bool catch_special_cases(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces);
    bool check_move_validity(const Move_data& move_start, const Move_data& move_end, 
                             std::vector<ChessPieces>& pieces);

                             
};

class Pawn : public ChessPieces{

    private:

    public:
        bool valid_move(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces);
        bool En_passant(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces);
};

class Bishop : public ChessPieces{

    private:

    public:
        bool valid_move(const Move_data& move_start, const Move_data& move_end);
};

class Knight : public ChessPieces{

    private:

    public:
        bool valid_move(const Move_data& move_start, const Move_data& move_end);
};

class Rook : public ChessPieces{

    private:

    public:
        bool valid_move(const Move_data& move_start, const Move_data& move_end);
};

class Queen : public ChessPieces{

    private:

    public:
        bool valid_move(const Move_data& move_start, const Move_data& move_end);
};

class King : public ChessPieces{

    private:

    public:
        bool valid_move(const Move_data& move_start, const Move_data& move_end);
        bool castling(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces);
        bool in_check(std::vector<ChessPieces>& pieces);
        bool checkmate();
        bool stalemate();
};
