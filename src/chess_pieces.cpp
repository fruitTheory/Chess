#include "chess_pieces.hpp"
#include "chess_clock.hpp"
#include "chess_utility.hpp"
#include "chess_history.hpp"
#include "config.hpp"
#include <iostream>


int piece_map[8][8] = 
{
    {29, 27, 25, 31, 32, 26, 28, 30},
    {17, 18, 19, 20, 21, 22, 23, 24},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {1,  2,  3,  4,  5,  6,  7,  8},
    {13, 11, 9, 15, 16, 10, 12, 14}
};

// Piece notations mapping
const std::map<char, Pieces> piece_notation_map = {
    {'N', Pieces::N},{'B', Pieces::B},{'R', Pieces::R},{'Q', Pieces::Q},{'K', Pieces::K}
};

// Letter notations mapping
const std::map<char, Letters> letter_notation_map = {
    {'a', Letters::a},{'b', Letters::b},{'c', Letters::c},{'d', Letters::d},
    {'e', Letters::e},{'f', Letters::f},{'g', Letters::g},{'h', Letters::h}
};

// Overload << operator for Pieces type
std::ostream& operator<<(std::ostream& outstream, const Pieces& value) {
    switch(value) 
    {
        case Pieces::None: outstream << 0; break;
        case Pieces::P: outstream << 1; break;
        case Pieces::B: outstream << 2; break;
        case Pieces::N: outstream << 3; break;
        case Pieces::R: outstream << 4; break;
        case Pieces::Q: outstream << 5; break;
        case Pieces::K: outstream << 6; break;
    }
    return outstream;
}

void ChessPieces::Set_Piece_ID(int ID){ object_id = ID; }
int ChessPieces::Get_Piece_ID(){ return object_id; }

void ChessPieces::Set_Color_ID(int ID){ color_id = ID; }
int ChessPieces::Get_Color_ID() { /* case of no piece */if(object_id == 0){return -1;} return color_id; }

void ChessPieces::Set_Has_Moved(int ID){ has_moved = ID; }
bool ChessPieces::Get_Has_Moved() { return has_moved; }

// Returns piece type, also determines amount of pieces for each type, based on object id
Pieces ChessPieces::get_piece_type() {
    
    if((object_id > 0 && object_id <= 8) || (object_id > 16 && object_id <= 24)) { return Pieces::P; }
    if(object_id == 9 || object_id == 10 || object_id == 25 || object_id == 26) { return Pieces::B; }
    if(object_id == 11 || object_id == 12 || object_id == 27 || object_id == 28) { return Pieces::N; }
    if(object_id == 13 || object_id == 14 || object_id == 29 || object_id == 30) { return Pieces::R; }

    if(object_id == 15 || object_id == 31) { return Pieces::Q;}
    if(object_id == 16 || object_id == 32) { return Pieces::K; }
    return Pieces::None;
}

// Return piece type in string format
std::string ChessPieces::get_piece_type_str(Pieces type){
        if(type == Pieces::P){ return "pawn";}
        if(type == Pieces::B){ return "bishop";}
        if(type == Pieces::N){ return "knight";}
        if(type == Pieces::R){ return "rook";}
        if(type == Pieces::Q){ return "queen";}
        if(type == Pieces::K){ return "king";}
    return "Null";
}

// Uses a vector of type ChessPieces to create 32 objects which are pushed to that vector
// Object id below 17 are white pieces
void ChessPieces::create_chess_pieces(std::vector<ChessPieces>& pieces){
        for(int i = 1; i <= 32; i++){
        ChessPieces piece;
        piece.Set_Piece_ID(i);
        piece.Set_Has_Moved(false);
        i < 17 ? piece.Set_Color_ID(1) : piece.Set_Color_ID(0);
        pieces.push_back(piece);
    } // create 32 objects with ID's
}
    /*
        ID Mapping for Chess Pieces:
    White Pieces:                   Black Pieces:
    // white_pawn_1   : 1           // black_pawn_1   : 17
    // white_pawn_2   : 2           // black_pawn_2   : 18
    // white_pawn_3   : 3           // black_pawn_3   : 19
    // white_pawn_4   : 4           // black_pawn_4   : 20
    // white_pawn_5   : 5           // black_pawn_5   : 21
    // white_pawn_6   : 6           // black_pawn_6   : 22
    // white_pawn_7   : 7           // black_pawn_7   : 23
    // white_pawn_8   : 8           // black_pawn_8   : 24
    // white_bishop_1 : 9           // black_bishop_1 : 25
    // white_bishop_2 : 10          // black_bishop_2 : 26
    // white_knight_1 : 11          // black_knight_1 : 27
    // white_knight_2 : 12          // black_knight_2 : 28
    // white_rook_1   : 13          // black_rook_1   : 29
    // white_rook_2   : 14          // black_rook_2   : 30
    // white_queen    : 15          // black_queen    : 31
    // white_king     : 16          // black_king     : 32    
    */

// Set  colors based on object id
void ChessPieces::set_piece_colors(std::vector<ChessPieces>& pieces){

    sf::Color piece_color = {0,0,255,255};

    for(int i = 0; i < 32; i++){
        
        //Pieces type = get_piece_type(pieces[i].object_id);
        Pieces type = pieces[i].get_piece_type();

        if(pieces[i].object_id <= 16){ piece_color = sf::Color::White; }
        if(pieces[i].object_id > 16 && pieces[i].object_id <= 32){ piece_color = sf::Color::Black; }

        if(type == Pieces::P){ pieces[i].pawn_shape.setFillColor(piece_color);}
        if(type == Pieces::B){ pieces[i].bishop_shape.setFillColor(piece_color);}
        if(type == Pieces::N){ pieces[i].knight_shape.setFillColor(piece_color);}
        if(type == Pieces::R){ pieces[i].rook_shape.setFillColor(piece_color);}
        if(type == Pieces::Q){ pieces[i].queen_shape.setFillColor(piece_color);}
        if(type == Pieces::K){ pieces[i].king_shape.setFillColor(piece_color);}

    }
}

// Set initial and current piece positions, id based
void ChessPieces::place_pieces(std::vector<ChessPieces>& pieces){

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            // Gets object id of current array position, and uses that as a 'filler' value for later arrays
            // Then only If a matching type is found, place that piece at current array position
            // Square map places because it has actual pixel values and same array position
            int map_value = piece_map[y][x]; 
            Pieces type = pieces[map_value-1].get_piece_type(); 

            if(type == Pieces::P){pieces[map_value-1].pawn_shape.setPosition(square_map[y][x].first, square_map[y][x].second);}
            if(type == Pieces::B) { pieces[map_value-1].bishop_shape.setPosition(square_map[y][x].first, square_map[y][x].second);}
            if(type == Pieces::N) { pieces[map_value-1].knight_shape.setPosition(square_map[y][x].first, square_map[y][x].second);}
            if(type == Pieces::R) { pieces[map_value-1].rook_shape.setPosition(square_map[y][x].first, square_map[y][x].second);}
            if(type == Pieces::Q) { pieces[map_value-1].queen_shape.setPosition(square_map[y][x].first, square_map[y][x].second);}
            if(type == Pieces::K) { pieces[map_value-1].king_shape.setPosition(square_map[y][x].first, square_map[y][x].second);}

        }
    }
}

// Draws all pieces
void ChessPieces::draw_pieces(sf::RenderWindow& window, std::vector<ChessPieces>& pieces){

    std::vector<int> map_values;
    Pieces type;
    
    // Get the current piece values
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){ 
            map_values.push_back( piece_map[y][x]); }
    }

    for(int i = 0; i < 64; i++){
        if(map_values[i] != 0){
            type = pieces[map_values[i]-1].get_piece_type();
            // I believe the trick for this is to have same map value as place_pieces()
            // So that it knows which exact piece is missing (after attack)
            // This method may not be specific enough, will see in future
            if(type == Pieces::P) { window.draw(pieces[map_values[i]-1].pawn_shape);}
            if(type == Pieces::B) { window.draw(pieces[map_values[i]-1].bishop_shape);}
            if(type == Pieces::N) { window.draw(pieces[map_values[i]-1].knight_shape);}
            if(type == Pieces::R) { window.draw(pieces[map_values[i]-1].rook_shape);}
            if(type == Pieces::Q) { window.draw(pieces[map_values[i]-1].queen_shape);}
            if(type == Pieces::K) { window.draw(pieces[map_values[i]-1].king_shape);}
        }

    }
}

// Setup chess board with drawn pieces and colors
void ChessPieces::update_pieces(sf::RenderWindow& window, Chessboard& board, std::vector<ChessPieces>& pieces){

    board.create(window);
    set_piece_colors(pieces);
    place_pieces(pieces);
    draw_pieces(window, pieces);
    
}

// Entry move function
bool ChessPieces::move_piece( sf::RenderWindow& window, Chessboard& board, 
                              ChessPieces& chess_pieces, std::vector<ChessPieces>& pieces,
                              ChessPieces::Move& move ) {
    
    ChessUtility utils;
    bool is_attack;
    bool move_valid;

    // Stored converted move data for start and end move
    move.start = convert_move(move.start, pieces);
    move.end = convert_move(move.end, pieces);

    // Move validity
    move_valid = check_move_validity(move.start, move.end, pieces);
    std::string piece_type_str = get_piece_type_str(move.start.piece_type);
    if(!move_valid){ 
        std::cout << "Not a valid " << piece_type_str << " move\n"; return false; 
    } else {
        stored_moves.push_back(move); // store move
        store_board_state(); // store previous
        //utils.print_game_history(); // print previous
        is_attack = check_attack(move.start, move.end);
    }
    // Needed for certain rules
    pieces[move.start.piece_id].Set_Has_Moved(true); 

    // Clear start piece space, and move start to end pos
    piece_map[move.start.number][move.start.letter] = 0;
    PIECE_END_ID = move.start.piece_id;

    store_board_state(); // store new
    //utils.print_game_history(); // print new

    // Re-draw everything
    update_pieces(window, board, pieces);
    draw_clock_display(window);

    return true;

}

// Convert move type to usable data for array and embed additional data
ChessPieces::Move_data ChessPieces::convert_move(const Move_data& move_input, std::vector<ChessPieces>& pieces){

    Move_data m_data;

    // inverse conversion for white - black would invert letter instead of number
    int invert_number_white = (8 - move_input.number) + 1;
    m_data.number = invert_number_white - 1;
    m_data.letter = move_input.letter - 1;

    // get the actual piece id - use it to check the object type and color through array
    m_data.piece_id = piece_map[m_data.number][m_data.letter];
    m_data.piece_type = pieces[m_data.piece_id-1].get_piece_type();
    m_data.color = pieces[m_data.piece_id-1].Get_Color_ID();

    return m_data;

}

// General move validity check
bool ChessPieces::check_move_validity(const Move_data& move_start, const Move_data& move_end, 
                                      std::vector<ChessPieces>& pieces){

    Pawn pawn;
    Bishop bishop;

    // stop from selecting an empty sqaure to move
    if(move_start.piece_id == 0){ puts("Not a valid piece"); return false; }

    // stop from moving to same square 
    if(move_start.number == move_end.number && move_start.letter == move_end.letter)
    { puts("Not a valid destination"); return false; }

    // If not the current players turn stop from moving
    if(move_start.color != players_turn){ std::cout << "Not this players turn" << std::endl; return false; };

    // stop from moving to occupied square
    // if(PIECE_END_ID_REF != 0)
    // { std::cout << "Warning: Space occupied" << std::endl; return false; }

    if(move_start.piece_type == Pieces::P) {if(!pawn.valid_move(move_start, move_end, pieces)){return false;}}
    if(move_start.piece_type == Pieces::B) {if(!bishop.valid_move(move_start, move_end, pieces)){return false;}}
    if(move_start.piece_type == Pieces::N) { return true; }
    if(move_start.piece_type == Pieces::R) { }
    if(move_start.piece_type == Pieces::Q) { }
    if(move_start.piece_type == Pieces::K) { }

    return true;

}

// Checks if move is valid and if it is an attack
bool Pawn::valid_move(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces){

    // user note fix white pawns capturing and diagonal moving
    int move_number_squares;

    if(move_start.color == PLAYER::WHITE){
        // !quirk needs to be reverse due to inverse of number for array reasons
        move_number_squares = move_start.number - move_end.number; 
    }else{ move_number_squares = abs(move_start.number - move_end.number); }

    // amount of squares piece will move horizontal
    int move_letter_squares = abs(move_end.letter - move_start.letter);

    // stop if piece is black and moving backwards, confused why this need be inverse
    if(move_start.color == PLAYER::BLACK && move_start.number > move_end.number){ return false; }

    // Pawn can only move two spots on first move, also note <= 0 stops sideways moves
    if(move_number_squares > 2 || move_number_squares <= 0){return false;}
    if(pieces[move_start.piece_id].Get_Has_Moved() == true && move_number_squares > 1){return false;};


    // ------------------------------------------------------ //
    // SPECIAL CASE: En Passant - needs to be at least before other diagonal logic

    // stores piece id to left and right of start piece
    int id_right =  piece_map[move_start.number][move_start.letter+1];
    int id_left = piece_map[move_start.number][move_start.letter-1];
    int id_player = piece_map[move_start.number][move_start.letter];

    // get piece type to left and right of start piece
    Pieces type_right = pieces[id_right-1].get_piece_type();
    Pieces type_left = pieces[id_left-1].get_piece_type();

    // get left and right color to see if enemy
    int color_right = pieces[id_right-1].Get_Color_ID();
    int color_left = pieces[id_left-1].Get_Color_ID();
    int color_player = pieces[id_player-1].Get_Color_ID();

    // std::cout << id_left << " " << id_player << " " << id_right << std::endl;
    // std::cout << type_left << " " << type_right << std::endl;
    // std::cout << color_left << " " << color_player << " " << color_right << std::endl;

    // note for later more logical order for this
    int attacked_piece_id = piece_map[move_end.number+1][move_end.letter];
    pieces[attacked_piece_id-1].Get_Has_Moved();
    // if type is a pawn and not of the same color and if move is diagonal consider move valid
    if((type_left == Pieces::P || type_right == Pieces::P) && (color_left != color_player || color_right != color_player)){
        if(move_number_squares == 1 && move_letter_squares == 1){ 
            if(move_start.color == PLAYER::WHITE){
                puts("En Passant!"); piece_map[move_end.number+1][move_end.letter] = 0; return true; } else{
                puts("En Passant!"); piece_map[move_end.number-1][move_end.letter] = 0; return true; }
        }
    } // just need to lastly check if it was previously the pawns first move && it was 2 spots
    // ------------------------------------------------------ //


    // stop move diagonal 2 spaces on first move or any move
    if((move_number_squares == 2 && move_letter_squares > 0) || move_letter_squares > 1){return false;}

    // stop from moving to occupied square if cannot attack
    if(move_letter_squares == 0 && PIECE_END_ID_REF != 0){return false;}

    // if move is diagonal, check if occupied - dont allow if not occupied
    if((move_number_squares == 1 && move_letter_squares == 1) && (PIECE_END_ID_REF == 0)){return false;}

    // if move is diagonal, and if occupied, cant attack if same color piece
    if((move_number_squares == 1 && move_letter_squares == 1) && (PIECE_END_ID_REF != 0
    && move_start.color == move_end.color)){ return false;}
    
    return true;
}

bool Bishop::valid_move(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces){
    return true;
}

// Check if move is an attack
bool ChessPieces::check_attack(const Move_data& move_start, const Move_data& move_end){

    // if opposite color an not empty square consider attack
    if(move_start.color != move_end.color && move_end.piece_id != 0){ puts("attack!"); return true;}

    return false;

}

// Board vision 
void ChessPieces::check_valid_squares(const Move_data& move_start, const Move_data& move_end){

}

/*

TODO Special Cases

En passant
Castling - queenside, kingside
Move storage - reverse moves - arrow keys
King state - checks / checkmate / stalemate
Piece promotion

*/