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
    switch (value){
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

void ChessPieces::Set_Object_ID(int ID){ object_id = ID; }
int ChessPieces::Get_Object_ID(){ return object_id; }

void ChessPieces::Set_Color_ID(int ID){ color_id = ID; }
int ChessPieces::Get_Color_ID(){ /* case of no piece */if(object_id == 0){return -1;} return color_id; }

void ChessPieces::Set_Has_Moved(bool moved){ has_moved = moved; }
bool ChessPieces::Get_Has_Moved(){ return has_moved; }

void ChessPieces::Set_Object_Value(Pieces type){ 
    switch (type){
        case Pieces::P: object_value = Piece_Value::Pawn; break;
        case Pieces::B: object_value = Piece_Value::Bishop; break;
        case Pieces::N: object_value = Piece_Value::Knight; break;
        case Pieces::R: object_value = Piece_Value::Rook; break;
        case Pieces::Q: object_value = Piece_Value::Queen; break;
        case Pieces::K: object_value = Piece_Value::Pawn; break;
        case Pieces::None: object_value = Piece_Value::None; break;
    }
}
Piece_Value ChessPieces::Get_Object_Value(){ return object_value; }

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
    switch (type){
        case Pieces::P: return "pawn";
        case Pieces::B: return "bishop";
        case Pieces::N: return "knight";
        case Pieces::R: return "rook";
        case Pieces::Q: return "queen";
        case Pieces::K: return "king";
        default: return "Null";
    }
}

// Pushes 32 ChessPiece objects to a pieces vector
void ChessPieces::create_chess_pieces(std::vector<ChessPieces>& pieces){
        for(int i = 1; i <= 32; i++){
        ChessPieces piece;
        piece.Set_Object_ID(i);
        piece.Set_Object_Value(piece.get_piece_type());
        piece.Set_Has_Moved(false);
        i < 17 ? piece.Set_Color_ID(1) : piece.Set_Color_ID(0);
        pieces.push_back(piece);
    }
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

        switch (type){
            case Pieces::P: pieces[i].pawn_shape.setFillColor(piece_color); break;
            case Pieces::B: pieces[i].bishop_shape.setFillColor(piece_color); break;
            case Pieces::N: pieces[i].knight_shape.setFillColor(piece_color); break;
            case Pieces::R: pieces[i].rook_shape.setFillColor(piece_color); break;
            case Pieces::Q: pieces[i].queen_shape.setFillColor(piece_color); break;
            case Pieces::K: pieces[i].king_shape.setFillColor(piece_color); break;
        }
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

            switch (type){
                case Pieces::P: pieces[map_value-1].pawn_shape.setPosition(square_map[y][x].first, square_map[y][x].second); break;
                case Pieces::B: pieces[map_value-1].bishop_shape.setPosition(square_map[y][x].first, square_map[y][x].second); break;
                case Pieces::N: pieces[map_value-1].knight_shape.setPosition(square_map[y][x].first, square_map[y][x].second); break;
                case Pieces::R: pieces[map_value-1].rook_shape.setPosition(square_map[y][x].first, square_map[y][x].second); break;
                case Pieces::Q: pieces[map_value-1].queen_shape.setPosition(square_map[y][x].first, square_map[y][x].second); break;
                case Pieces::K: pieces[map_value-1].king_shape.setPosition(square_map[y][x].first, square_map[y][x].second); break;
            }


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
            switch (type){
                case Pieces::P: window.draw(pieces[map_values[i]-1].pawn_shape); break;
                case Pieces::B: window.draw(pieces[map_values[i]-1].bishop_shape); break;
                case Pieces::N: window.draw(pieces[map_values[i]-1].knight_shape); break;
                case Pieces::R: window.draw(pieces[map_values[i]-1].rook_shape); break;
                case Pieces::Q: window.draw(pieces[map_values[i]-1].queen_shape); break;
                case Pieces::K: window.draw(pieces[map_values[i]-1].king_shape); break;
            }
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
                              std::vector<ChessPieces>& pieces, ChessPieces::Move& move ) {
    
    ChessUtility utils;
    bool move_valid;
    extern int move_count;

    // Stored converted move data for start and end move
    move.start = convert_move(move.start, pieces);
    move.end = convert_move(move.end, pieces);

    // Move validity
    move_valid = check_move_validity(move.start, move.end, pieces);

    // Even if Move is not valid, if is a special case override move
    if(catch_special_cases(move.start, move.end, pieces)){ move_valid = true;}

    if(!move_valid){ 
        std::string piece_type_str = get_piece_type_str(move.start.piece_type);
        std::cout << "Not a valid " << piece_type_str << " move\n"; return false; 
    } else {
        // Below done if move is valid
        stored_moves.push_back(move); // store move
        ++move_count;
        store_board_state(); // store previous
        set_piece(move, pieces);
        store_board_state(); // store new
        //utils.print_game_history(); // print new
    }

    // Re-draw everything
    update_pieces(window, board, pieces);
    draw_clock_white(window); draw_clock_black(window);

    return true;

}

// Set end position to piece id and start position to empty
void ChessPieces::set_piece(Move move, std::vector<ChessPieces>& pieces){
    // Clear start piece space, and move start to end pos
    piece_map[move.start.number][move.start.letter] = 0;
    PIECE_END_ID = move.start.piece_id;
    pieces[move.start.piece_id-1].Set_Has_Moved(true); // Needed for certain rules
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

// General move validity checks
bool ChessPieces::check_move_validity(const Move_data& move_start, const Move_data& move_end, 
                                      std::vector<ChessPieces>& pieces){

    Pawn pawn;
    Bishop bishop;
    Knight knight;
    Rook rook;
    Queen queen;
    King king;

    // stop from selecting an empty sqaure to move
    if(move_start.piece_id == 0){ puts("Not a valid piece"); return false; }

    // stop from moving to same square 
    if(move_start.number == move_end.number && move_start.letter == move_end.letter)
    { puts("Not a valid destination"); return false; }

    // If not the current players turn stop from moving
    if(move_start.color != players_turn){ std::cout << "Not this players turn" << std::endl; return false; };

    // stop from moving to occupied space of same color
    if(PIECE_END_ID_REF != 0 && (move_start.color == move_end.color)){
         std::cout << "Warning: Space occupied" << std::endl; return false; }

    // if not a knight check path obstruction
    if(move_start.piece_type != Pieces::N){ if(check_obstruction(move_start, move_end, pieces)){
        std::cout << "Warning: Path obstructed" << std::endl; return false; }
    }

    // check if valid move for specific piece
    switch (move_start.piece_type){
        case Pieces::P: if(!pawn.valid_move(move_start, move_end, pieces)) return false; break;
        case Pieces::B: if(!bishop.valid_move(move_start, move_end)) return false; break;
        case Pieces::N: if(!knight.valid_move(move_start, move_end)) return false; break;
        case Pieces::R: if(!rook.valid_move(move_start, move_end)) return false; break;
        case Pieces::Q: if(!queen.valid_move(move_start, move_end)) return false; break;
        case Pieces::K: if(!king.valid_move(move_start, move_end)) return false; break;
    }

    return true;

}

// Returns both letter and number distance in an array, 0 for letter 1 for number
std::array<int, 2> ChessPieces::get_move_distance(const Move_data& move_start, const Move_data& move_end){

    std::array<int, 2>move_distance;

    // [0] will be amount of horizontal squares and [1] will be vertical
    move_distance[0] = abs(move_end.letter - move_start.letter);

    // !quirk needs to be reverse due to inverse number pos in array
    if((move_start.color == PLAYER::WHITE) && (move_start.piece_type == Pieces::P)){ 
        move_distance[1] = move_start.number - move_end.number; 
    } 
    else { move_distance[1] = abs(move_start.number - move_end.number); }

    return move_distance;
}

// Checks if move is valid and if it is an attack
bool Pawn::valid_move(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces){

    int dist_letter_squares = get_move_distance(move_start, move_end)[0];
    int dist_number_squares = get_move_distance(move_start, move_end)[1];

    // stop if piece is black and moving backwards, reverse if board flipped
    if(move_start.color == PLAYER::BLACK && move_start.number > move_end.number){ return false; }

    // Pawn can only move two spots on first move, also note <= 0 stops sideways moves
    if(dist_number_squares > 2 || dist_number_squares <= 0){return false;}
    if(pieces[move_start.piece_id].Get_Has_Moved() == true && dist_number_squares > 1){return false;};

    // if pawn attack check en passant - if passant is true capture passed pawn 
    if(dist_number_squares == 1 && dist_letter_squares == 1){ 
        if(En_passant(move_start, move_end, pieces)){
            if(move_start.color == PLAYER::WHITE){
                piece_map[move_end.number+1][move_end.letter] = 0; } else{ 
                piece_map[move_end.number-1][move_end.letter] = 0; }
            puts("En Passant!");
            return true;
        }
    }
    // stop move diagonal 2 spaces on first move or any move
    if((dist_number_squares == 2 && dist_letter_squares > 0) || dist_letter_squares > 1){return false;}

    // stop from moving to occupied square if cannot attack
    if(dist_letter_squares == 0 && PIECE_END_ID_REF != 0){return false;}

    // if move is diagonal, check if occupied - dont allow if not occupied
    if((dist_number_squares == 1 && dist_letter_squares == 1) && (PIECE_END_ID_REF == 0)){return false;}

    // if move is diagonal, and if occupied, cant attack if same color piece
    if((dist_number_squares == 1 && dist_letter_squares == 1) && (PIECE_END_ID_REF != 0
    && move_start.color == move_end.color)){ return false;}
    
    return true;
}

bool Pawn::En_passant(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces){

    // previous move info
    int previous_move_start_number = stored_moves[move_count-1].start.number;
    int previous_move_end_letter = stored_moves[move_count-1].end.letter;
    int previous_move_end_number = stored_moves[move_count-1].end.number;
    int previous_move_length = abs(previous_move_start_number - previous_move_end_number);

    // player info
    int id_player = piece_map[move_start.number][move_start.letter];
    int color_player = pieces[id_player-1].Get_Color_ID();

    // get enemy piece id
    int enemy_piece_id;
    if(move_start.color == PLAYER::WHITE){
        enemy_piece_id = piece_map[move_end.number+1][move_end.letter]; 
    } else {
        enemy_piece_id = piece_map[move_end.number-1][move_end.letter]; }

    // enemy info - check first if player is white or black
    int enemy_color_id = pieces[enemy_piece_id-1].Get_Color_ID();
    Pieces enemy_type = pieces[enemy_piece_id-1].get_piece_type();

    // Get the id of previous move and compare with attacked piece id
    int previous_move_id = piece_map[previous_move_end_number][previous_move_end_letter];
    if(previous_move_id != enemy_piece_id){ return false; }

    // if type is a pawn and not of the same color and if move is diagonal consider move valid
    if(previous_move_length == 2 && (enemy_type == Pieces::P && enemy_color_id != color_player))
    {
        puts("logic passed");
        return true;
    }

    return false;

}

bool Bishop::valid_move(const Move_data& move_start, const Move_data& move_end){

    int dist_letter_squares = get_move_distance(move_start, move_end)[0];
    int dist_number_squares = get_move_distance(move_start, move_end)[1];

    // stop from moving horizontally
    if(!( dist_number_squares >= 1 && dist_letter_squares >= 1 )){return false;}
    // must be stair-stepped
    if(( dist_number_squares != dist_letter_squares )){return false;}

    return true;
}

bool Knight::valid_move(const Move_data& move_start, const Move_data& move_end){

    int dist_letter_squares = get_move_distance(move_start, move_end)[0];
    int dist_number_squares = get_move_distance(move_start, move_end)[1];

    // stop move just one square
    if( dist_number_squares <= 1 && dist_letter_squares <= 1 ){return false;}
    // stop move more than 2 square
    if( dist_number_squares > 2 || dist_letter_squares > 2 ){return false;}

    // only allow +2 for number or letter, and + 1 on opposite 
    if( dist_number_squares == 2 && dist_letter_squares != 1 ){return false;}
    if( dist_letter_squares == 2 && dist_number_squares != 1 ){return false;}

    return true;
}

bool Rook::valid_move(const Move_data& move_start, const Move_data& move_end){

    int dist_letter_squares = get_move_distance(move_start, move_end)[0];
    int dist_number_squares = get_move_distance(move_start, move_end)[1];

    // stop from moving diagonally
    if( dist_number_squares >= 1 && dist_letter_squares >= 1 ){return false;}

    return true;
}

bool Queen::valid_move(const Move_data& move_start, const Move_data& move_end){

    // int dist_letter_squares = get_move_distance(move_start, move_end)[0];
    // int dist_number_squares = get_move_distance(move_start, move_end)[1];

    // queen can move anywhere

    return true;
}

bool King::valid_move(const Move_data& move_start, const Move_data& move_end){

    int dist_letter_squares = get_move_distance(move_start, move_end)[0];
    int dist_number_squares = get_move_distance(move_start, move_end)[1];

    // stop from moving more than one space
    if( dist_number_squares > 1 || dist_letter_squares > 1 ){return false;}

    return true;
}

// Check if move is an attack
bool ChessPieces::check_attack(const Move_data& move_start, const Move_data& move_end){

    // if not an empty square and opposite color piece consider attack
    if(move_start.color != move_end.color && move_end.piece_id != 0){ puts("attack!"); return true;}

    return false;

}

// Basic board vision for game logic 
bool ChessPieces::check_obstruction(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces){

    int dist_letter_squares = get_move_distance(move_start, move_end)[0];
    int dist_number_squares = get_move_distance(move_start, move_end)[1];

    // get gap amount between start and end
    int dist_letter_gap = dist_letter_squares - 1;
    int dist_number_gap = dist_number_squares - 1;

    int piece_id;
    DIRECTION direction = get_move_direction(move_start, move_end);

    // Check for piece direction and if theres obscurification
    switch(direction){

        case DIRECTION::DOWN:{
            for(int x = 0; x < dist_number_squares; x++){
                piece_id = piece_map[move_start.number - x][move_start.letter];
                if(x > 0 && piece_id != 0){ return true; }
            }
            break;
        }
        case DIRECTION::UP:{
            for(int x = 0; x < dist_number_squares; x++){
                piece_id = piece_map[move_start.number + x][move_start.letter];
                if(x > 0 && piece_id != 0){ return true; }
            }
            break;
        }
        case DIRECTION::LEFT:{
            for(int x = 0; x < dist_letter_squares; x++){
                piece_id = piece_map[move_start.number][move_start.letter - x];
                if(x > 0 && piece_id != 0){ return true; }
            }
            break;
        }
        case DIRECTION::RIGHT:{
            for(int x = 0; x < dist_letter_squares; x++){
                piece_id = piece_map[move_start.number][move_start.letter + x];
                if(x > 0 && piece_id != 0){ return true; }
            }
            break;
        }
        case DIRECTION::DOWN_LEFT:{
            for(int x = 0; x < dist_number_squares; x++){
                piece_id = piece_map[move_start.number - x][move_start.letter - x];
                if(x > 0 && piece_id != 0){ return true; }
            }
            break;
        }
        case DIRECTION::DOWN_RIGHT:{
            for(int x = 0; x < dist_number_squares; x++){
                piece_id = piece_map[move_start.number - x][move_start.letter + x];
                if(x > 0 && piece_id != 0){ return true; }
            }
            break;
        }
        case DIRECTION::UP_LEFT:{
            for(int x = 0; x < dist_number_squares; x++){
                piece_id = piece_map[move_start.number + x][move_start.letter - x];
                if(x > 0 && piece_id != 0){ return true; }
            }
            break;
        }
        case DIRECTION::UP_RIGHT:{
            for(int x = 0; x < dist_number_squares; x++){
                piece_id = piece_map[move_start.number + x][move_start.letter + x];
                if(x > 0 && piece_id != 0){ return true; }
            }
            break;
        }
        default: break;
    }

    return false;

}

// Returns both letter and number distance in an array, 0 for letter 1 for number
DIRECTION ChessPieces::get_move_direction(const Move_data& move_start, const Move_data& move_end){

    DIRECTION direction;

    // number distance based on board travel
    int number_distance = move_end.number - move_start.number; // negative down board
    int letter_distance = move_end.letter - move_start.letter; // negative left board

    if(number_distance < 0){ direction = DIRECTION::DOWN; }
    if(number_distance > 0){ direction = DIRECTION::UP; }
    if(letter_distance < 0){ direction = DIRECTION::LEFT; }
    if(letter_distance > 0){ direction = DIRECTION::RIGHT; }

    if(number_distance < 0 && letter_distance < 0){ direction = DIRECTION::DOWN_LEFT; }
    if(number_distance < 0 && letter_distance > 0){ direction = DIRECTION::DOWN_RIGHT;}
    if(number_distance > 0 && letter_distance < 0){ direction = DIRECTION::UP_LEFT; }
    if(number_distance > 0 && letter_distance > 0){ direction = DIRECTION::UP_RIGHT; }

    return direction;
}

bool ChessPieces::catch_special_cases(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces){
    
    King king;
    
    // if(move_start.piece_type == Pieces::K){

    //     if(move_start.piece_type == Pieces::K && king.castling(move_start, move_end, pieces)){ puts("castling"); return true;}
    //     // if(king.in_check()){ puts("king in check"); }
    //     // if(king.checkmate()){ puts("king checkmated"); }
    //     // if(king.stalemate()){ puts("king stalemated"); }
    // }
    
    if(move_start.piece_type == Pieces::K 
    && king.castling(move_start, move_end, pieces)){ 
        puts("castling"); return true;
    }

    puts("special");\
    // note need to figure out, how player can block this check if this is raised
    if(king.in_check(pieces)){ puts("king in check"); return false;}

    return false;

}

bool King::in_check(std::vector<ChessPieces>& pieces){

    ChessUtility util;
    sf::Vector2i white_king_position;
    sf::Vector2i black_king_position;
    int white_king_x;
    int white_king_y;
    int black_king_x;
    int black_king_y;

    white_king_position = util.find_piece_position(KING_WHITE);
    white_king_x = white_king_position.x;
    white_king_y = white_king_position.y;

    black_king_position = util.find_piece_position(KING_BLACK);
    black_king_x = black_king_position.x;
    black_king_y = black_king_position.y;

    // std::cout << "king white y: " << white_king_y << std::endl;
    // std::cout << "king white x: " << white_king_x << std::endl;
    // std::cout << "king black y: " << black_king_y << std::endl;
    // std::cout << "king black x: " << black_king_x << std::endl;

    Pieces piece_type;
    int piece_id;
    int piece_color;
    int king_y = NULL;
    int king_x = NULL;

    // Note this needs to be inverse to activate on correct players turn
    if((players_turn == PLAYER::WHITE)){
        king_y = white_king_y;
        king_x = white_king_x;
    } else {
        king_y = black_king_y;
        king_x = black_king_x;
    }

    // std::cout << "king y: " << king_y << std::endl;
    // std::cout << "king x: " << king_x << std::endl;

    std::vector<std::pair<Pieces, int>> pieces_hit; // array of pieces hit

    // Find the type of pieces down board (behind white)
    for(int y = 1; y < 8; y++){ 
        if(!(king_y + y > 7)){ // array out of bounds
            piece_id = piece_map[king_y + (y)][king_x];
            piece_type = pieces[piece_id-1].get_piece_type();
            piece_color = pieces[piece_id-1].Get_Color_ID();
            if(piece_type != Pieces::None){ // stopping at first piece hit
                std::cout << "d ";
                std::cout << piece_type << std::endl;
                std::cout << "color d ";
                std::cout << piece_color << std::endl;
                pieces_hit.push_back(std::make_pair(piece_type, piece_color));
                break;
            }
        }
    }

    // Find the type of pieces up board (infront white)
    for(int y = 1; y < 8; y++){ 
        if(!(king_y + -(y) < 0)){ // array out of bounds
            piece_id = piece_map[king_y + -(y)][king_x];
            piece_type = pieces[piece_id-1].get_piece_type();
            piece_color = pieces[piece_id-1].Get_Color_ID();
            if(piece_type != Pieces::None){ // stopping at first piece hit
                std::cout << "u ";
                std::cout << piece_type << std::endl;
                std::cout << "color u ";
                std::cout << piece_color << std::endl;
                pieces_hit.push_back(std::make_pair(piece_type, piece_color));
                break;
            }
        }
    }

    // Find the type of pieces to the left
    for(int x = 1; x < 8; x++){ 
        if(!(king_x + -(x) < 0)){ // array out of bounds
            piece_id = piece_map[king_y][king_x + -(x)];
            piece_type = pieces[piece_id-1].get_piece_type();
            piece_color = pieces[piece_id-1].Get_Color_ID();
            if(piece_type != Pieces::None){ // stopping at first piece hit
                std::cout << "l ";
                std::cout << piece_type << std::endl;
                std::cout << "color l ";
                std::cout << piece_color << std::endl;
                pieces_hit.push_back(std::make_pair(piece_type, piece_color));
                break;
            }
        }
    }

    // Find the type of pieces to the right
    for(int x = 1; x < 8; x++){ 
        if(!(king_x + + (x) > 7)){ // array out of bounds
            piece_id = piece_map[king_y][king_x + (x)];
            piece_type = pieces[piece_id-1].get_piece_type();
            piece_color = pieces[piece_id-1].Get_Color_ID();
            if(piece_type != Pieces::None){ // stopping at first piece hit
                std::cout << "r ";
                std::cout << piece_type << std::endl;
                std::cout << "color r ";
                std::cout << piece_color << std::endl;
                pieces_hit.push_back(std::make_pair(piece_type, piece_color));
                break;
            }
        }
    }

    // Find the type of pieces to the down right
    for(int z = 1; z < 8; z++){ 
        if(!(king_y + (z) > 7) && !(king_x + (z) > 7)){ // array out of bounds
            piece_id = piece_map[king_y + (z)][king_x + (z)];
            piece_type = pieces[piece_id-1].get_piece_type();
            piece_color = pieces[piece_id-1].Get_Color_ID();
            if(piece_type != Pieces::None){ // stopping at first piece hit
                std::cout << "dr ";
                std::cout << piece_type << std::endl;
                std::cout << "color dr ";
                std::cout << piece_color << std::endl;
                pieces_hit.push_back(std::make_pair(piece_type, piece_color));
                break;
            }
        }
    }

    // Find the type of pieces to the up right
    for(int z = 1; z < 8; z++){ 
        if(!(king_y + -(z) < 0) && !(king_x + (z) > 7)){ // array out of bounds
            piece_id = piece_map[king_y + -(z)][king_x + (z)];
            piece_type = pieces[piece_id-1].get_piece_type();
            piece_color = pieces[piece_id-1].Get_Color_ID();
            if(piece_type != Pieces::None){ // stopping at first piece hit
                std::cout << "ur ";
                std::cout << piece_type << std::endl;
                std::cout << "color ur ";
                std::cout << piece_color << std::endl;
                pieces_hit.push_back(std::make_pair(piece_type, piece_color));
                break;
            }
        }
    }

    // Find the type of pieces to the up left
    for(int z = 1; z < 8; z++){ 
        if(!(king_y + -(z) < 0) && !(king_x + -(z) < 0)){ // array out of bounds
            piece_id = piece_map[king_y + -(z)][king_x + -(z)];
            piece_type = pieces[piece_id-1].get_piece_type();
            piece_color = pieces[piece_id-1].Get_Color_ID();
            if(piece_type != Pieces::None){ // stopping at first piece hit
                std::cout << "ul ";
                std::cout << piece_type << std::endl;
                std::cout << "color ul ";
                std::cout << piece_color << std::endl;
                pieces_hit.push_back(std::make_pair(piece_type, piece_color));
                break;
            }
        }
    }

    // Find the type of pieces to the down left
    for(int z = 1; z < 8; z++){ 
        if(!(king_y + (z) > 7) && !(king_x + -(z) < 0)){ // array out of bounds
            piece_id = piece_map[king_y + (z)][king_x + -(z)];
            piece_type = pieces[piece_id-1].get_piece_type();
            piece_color = pieces[piece_id-1].Get_Color_ID();
            if(piece_type != Pieces::None){ // stopping at first piece hit
                std::cout << "dl ";
                std::cout << piece_type << std::endl;
                std::cout << "color dl ";
                std::cout << piece_color << std::endl;
                pieces_hit.push_back(std::make_pair(piece_type, piece_color));
                break;
            }
        }
    }

    for(int x = 0; x < pieces_hit.size(); x++){
        if(pieces_hit.at(x).second != players_turn){
            return true;
        }
    }

    // std::cout << "size: " << pieces_hit.size() << "\n";
    // std::cout << pieces_hit.at(0) << "\n";
    // pieces_hit.clear();
    puts("");

    return false;

}
bool King::checkmate(){
    // if check is true, can king move to a non occupied sqaure
    // check lines around king then special case knight
}
bool King::stalemate(){
    // filter for every piece left on board
    // test if any of legal move
}

bool King::castling(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces){
    
    /* Before anything happens check if path physically obstructed */
    if(check_obstruction(move_start, move_end, pieces)){ return false; }

    /* Check if pieces involved have moved yet, if so makes castling invalid */

    bool long_white_rook_moved = pieces[ROOK_WHITE_1 - 1].Get_Has_Moved();
    bool short_white_rook_moved = pieces[ROOK_WHITE_2 - 1].Get_Has_Moved();
    bool white_king_moved = pieces[KING_WHITE - 1].Get_Has_Moved();

    bool long_black_rook_moved = pieces[ROOK_BLACK_1 - 1].Get_Has_Moved();
    bool short_black_rook_moved = pieces[ROOK_BLACK_2 - 1].Get_Has_Moved();
    bool black_king_moved = pieces[KING_BLACK - 1].Get_Has_Moved();

    /* If king has moved in any case will make castling invalid */

    int player = move_start.color;
    if(player == PLAYER::WHITE && white_king_moved == true
    || player == PLAYER::BLACK && black_king_moved == true)
    { return false; }

    /* Distance to check if not within castling range */
    int dist_letter_squares = get_move_distance(move_start, move_end)[0];
    ChessPieces::Move move;
    DIRECTION direction = get_move_direction(move_start, move_end);

    /* please note if board is ever flipped the directions would be inverted
        maybe cheap way to help would just be creating an invert direction func */

    switch(direction){
        case DIRECTION::LEFT:{
            // Queenside
            if(player == PLAYER::WHITE 
            && long_white_rook_moved == false 
            && dist_letter_squares == 3)
            {
                move.start.letter = 0; move.start.number = 7;
                move.end.letter = 2; move.end.number = 7;
                move.start.piece_id = ROOK_WHITE_1;

                set_piece(move, pieces);

                return true;
            }
            if(player == PLAYER::BLACK 
            && long_black_rook_moved == false 
            && dist_letter_squares == 3)
            {
                move.start.letter = 0; move.start.number = 0;
                move.end.letter = 2; move.end.number = 0;
                move.start.piece_id = ROOK_BLACK_1;

                set_piece(move, pieces);

                return true;
            }
        }
            break;
        case DIRECTION::RIGHT:{
            // Kingside
            if(player == PLAYER::WHITE 
            && short_white_rook_moved == false 
            && dist_letter_squares == 2)
            {
                move.start.letter = 7; move.start.number = 7;
                move.end.letter = 5; move.end.number = 7;
                move.start.piece_id = ROOK_WHITE_2;

                set_piece(move, pieces);

                return true;
            }
            if(player == PLAYER::BLACK 
            && short_black_rook_moved == false 
            && dist_letter_squares == 2)
            {
                move.start.letter = 7; move.start.number = 0;
                move.end.letter = 5; move.end.number = 0;
                move.start.piece_id = ROOK_BLACK_2;

                set_piece(move, pieces);

                return true;
            }
        }
            break;
        default:
            break;
    }

    return false;
}


/*

TODO Special Cases

King state - checks / checkmate / stalemate
Enemy blocking castling
Piece promotion

Extra: go back and forward in history with arrow keys

*/