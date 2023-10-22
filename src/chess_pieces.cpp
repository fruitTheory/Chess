#include "chess_pieces.hpp"
#include "chess_clock.hpp"
#include <iostream>
#include <utility>
#include <future>

// Constructor
ChessPieces::ChessPieces():
null_shape(0.f, 0),
pawn_shape(48.f, 3),
bishop_shape(48.f, 4),
knight_shape(48.f, 5),
rook_shape(48.f, 6),
king_shape(48.f, 8),
queen_shape(48.f, 100)
{

}

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

void ChessPieces::Set_Piece_ID(int ID){ object_id = ID; }
int ChessPieces::Get_Piece_ID(){ return object_id; }

void ChessPieces::Set_Color_ID(int ID){ color_id = ID; }
int ChessPieces::Get_Color_ID() { return color_id; }

void ChessPieces::Set_Has_Moved(int ID){ has_moved = ID; }
int ChessPieces::Get_Has_Moved() { return has_moved; }

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

// Uses a vector of type ChessPieces to create 32 objects which are pushed to that vector
// Object id below 17 are white pieces
void ChessPieces::create_chess_pieces(std::vector<ChessPieces>& pieces){
        for(int i = 1; i <= 32; i++){
        ChessPieces piece;
        piece.Set_Piece_ID(i);
        piece.Set_Has_Moved(0);
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

// Set initial and current piece positions
void ChessPieces::place_pieces(std::vector<ChessPieces>& pieces){

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            // note that the object id returned from map_value is an abstract version not the class version
            int map_value = piece_map[y][x]; // an objects id at a started position position ex:{0, 0}
            Pieces type = pieces[map_value-1].get_piece_type(); // type of piece that object id is

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

    for(int i = 0; i < 32; i++){

    //Pieces type = get_piece_type(pieces[i].object_id);
    Pieces type = pieces[i].get_piece_type();

    if(type == Pieces::P) { window.draw(pieces[i].pawn_shape);}
    if(type == Pieces::B) { window.draw(pieces[i].bishop_shape);}
    if(type == Pieces::N) { window.draw(pieces[i].knight_shape);}
    if(type == Pieces::R) { window.draw(pieces[i].rook_shape);}
    if(type == Pieces::Q) { window.draw(pieces[i].queen_shape);}
    if(type == Pieces::K) { window.draw(pieces[i].king_shape);}

    }
}

// Use to setup initial chess board with pieces, sets colors, places pieces, render and display them
void ChessPieces::update_pieces(sf::RenderWindow& window, Chessboard& board, std::vector<ChessPieces>& pieces){

    board.create(window);
    set_piece_colors(pieces);
    place_pieces(pieces);
    draw_pieces(window, pieces);
    
}

// Call to get user input through cin
std::string get_user_input() {
    std::string user_input;
    std::cin >> user_input;
    return user_input;
}

// Returns player piece selection or piece destination
ChessPieces::Move_data ChessPieces::get_move_input(sf::RenderWindow& window, Chessboard& board,
                                                     ChessPieces& chess_pieces, std::vector<ChessPieces>& pieces){

    ChessPieces::Move_data move;
    std::string input_move;
    std::future<std::string> user_input;

    bool user_has_input = false;

    select_piece:

    user_input = std::async(std::launch::async, get_user_input);

    while(user_has_input == false){
        auto status = user_input.wait_for(std::chrono::milliseconds(1000));
        // if receive input, store it and break loop, else redraw board and wait
        if(status == std::future_status::ready){
            input_move = user_input.get();
            break;
        } 
        else{ initialize_render(window, board, chess_pieces, pieces); }
    }

    // test valid move lengths and catch values that are out of range
    try{
        if(input_move.length() == 2){
            move.piece_type = Pieces::P;
            move.letter = static_cast<int>(letter_notation_map.at(input_move[0]));
            move.number = input_move[1] - '0';
        }
        else if(input_move.length() == 3){
            move.piece_type = (piece_notation_map.at(input_move[0]));
            move.letter = static_cast<int>(letter_notation_map.at(input_move[1]));
            move.number = input_move[2] - '0'; // -'0' converts 0-9 char to numeral
        }
        else{ std::cout << "Not a valid piece" << std::endl; goto select_piece;}
        
    } catch(const std::out_of_range& err){ std::cout << "Not a valid piece" << std::endl; goto select_piece; }

    return move;
}


bool ChessPieces::move_piece(sf::RenderWindow& window, Chessboard& board, 
                            ChessPieces& chess_pieces, std::vector<ChessPieces>& pieces){

    Pieces type;
    ChessPieces::Move move;
    ChessPieces::Move_data move_data;
    int color_id;

    move_input:
    std::cout << "Select a piece and destination - Ex: Bc1 f4, c2 c4, Ng1 Nf3\n";

    // returns raw user move data
    move.start = get_move_input(window, board, chess_pieces, pieces);
    move.end = get_move_input(window, board, chess_pieces, pieces);

    // convert data
    move.start = convert_move(move.start, pieces);
    move.end = convert_move(move.end, pieces);

    

    bool move_valid = check_move_validity(move.start, move.end, pieces);
    if(!move_valid){ puts("Not a valid move");goto move_input; }
    pieces[move.start.piece_id].Set_Has_Moved(1); // set for certain rules


    // clear start piece space    // move start piece to end pos
    piece_map[move.start.number][move.start.letter] = 0;
    piece_map[move.end.number][move.end.letter] = move.start.piece_id;


    // re-setup everything
    update_pieces(window, board, pieces);
    update_clock_display(window);

    return true;

}

// General convert move into usable data for array based on black or white player
ChessPieces::Move_data ChessPieces::convert_move(const Move_data& move_input, std::vector<ChessPieces>& pieces){

    Move_data move_output;

    // if(player black, invert letter instead of number)

    // conversion for white
    int invert_number_white = (8 - move_input.number) + 1;
    move_output.number = invert_number_white - 1;
    move_output.letter = move_input.letter - 1;

    // get the actual piece id - use it to check the object type and color through array
    move_output.piece_id = piece_map[move_output.number][move_output.letter];
    move_output.piece_type = pieces[move_output.piece_id-1].get_piece_type();
    move_output.color = pieces[move_output.piece_id-1].Get_Color_ID();

    std:: cout << pieces[move_output.piece_id].Get_Has_Moved() << " convert " << std::endl;

    return move_output;

}

// General move validity check
bool ChessPieces::check_move_validity(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces){

    Pawn pawn;

    // check if selected piece(id) is null
    if(move_start.piece_id == 0){ std::cout << "Not a valid piece" << std::endl; return false; }

    // stop from moving to same square 
    if(move_start.number == move_end.number && move_start.letter == move_end.letter)
    { std::cout << "Not a valid destination" << std::endl; return false; }

    // stop from moving to occupied square
    if(!(piece_map[move_end.number][move_end.letter]) == 0)
    { std::cout << "Warning: Space occupied" << std::endl; return false; }

    if(move_start.piece_type == Pieces::P) { if(!pawn.valid_move(move_start, move_end, pieces)){return false;}}
    if(move_start.piece_type == Pieces::B) { }
    if(move_start.piece_type == Pieces::N) { }
    if(move_start.piece_type == Pieces::R) { }
    if(move_start.piece_type == Pieces::Q) { }
    if(move_start.piece_type == Pieces::K) { }

    return true;

}

bool Pawn::valid_move(const Move_data& move_start, const Move_data& move_end, std::vector<ChessPieces>& pieces){

    // !quirk needs to be reverse due to inverse of number for array reasons
    int move_sqaures = move_start.number - move_end.number; 

    // Pawn can only move two spots on first move
    if(move_sqaures > 2 || move_sqaures <= 0){return false;}
    if(pieces[move_start.piece_id].Get_Has_Moved() == 1 && move_sqaures > 1){return false;};

    return true;
}

/*
TODO

Move storage - reverse moves - arrow keys
King state - checks / checkmate / stalemate
Piece promotion

*/

/*
Takes input: a6->a7, Bb7, Ne4, Ke8->Kd7
Stores input: Go back left arrow 
- If obstruction found check if white or black
- If opposite color and piece can attack then take piece and stop there

- Checks if piece is obstructing path (how?)
    one possibility, we have a basic representation of board as a linear array
    check if any point along the path is not a 0 (how?)
        we need to take into consideration the piece path ability(left right up down, diagonal, abstracted(N))
        diagonal will need a check if result is to the right or left, and higher or lower(behind)
            ex: upper right, +1 up board +1 right [6+1][e+1] = [7][f] and again until final is reached
            to check compare - [6][e] ? [8][h], if [input] < [target] + 1 : if [input] > [target] -1
        left right - Ra4 -> Rf4 , if input < target + 1 - covers all cases
        knight - +2 up/down/ +1 left/right -- +2 left/right +1 up/down

        Note that this is 2D thinking, can we do it in 1D with just the linear array
            sure with math - 8x8 = 64, well 0 is A8, but 63 is A1 currently


*/