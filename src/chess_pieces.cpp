#include "chess_pieces.hpp"
#include "chess_utility.hpp"
#include <iostream>
#include <utility>

// Constructor
ChessPieces::ChessPieces():
null(0.f, 0),
pawn(48.f, 3),
bishop(48.f, 4),
knight(48.f, 5),
rook(48.f, 6),
king(48.f, 8),
queen(48.f, 100)
{

}

int piece_map_v2[8][8] = 
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

// Sets objects int object_id
void ChessPieces::Set_ID(int ID){ object_id = ID; }

// Returns objects int object_id
int ChessPieces::Get_ID(){ return object_id; }

// Returns a piece type, also determines the amount of pieces for each type, based on the object id
Pieces ChessPieces::get_piece_type() {
    
    if(object_id > 0 && object_id <= 8 || (object_id > 16 && object_id <= 24)) { return Pieces::P; }
    if(object_id == 9 || object_id == 10 || object_id == 25 || object_id == 26) { return Pieces::B; }
    if(object_id == 11 || object_id == 12 || object_id == 27 || object_id == 28) { return Pieces::N; }
    if(object_id == 13 || object_id == 14 || object_id == 29 || object_id == 30) { return Pieces::R; }

    if(object_id == 15 || object_id == 31) { return Pieces::Q;}
    if(object_id == 16 || object_id == 32) { return Pieces::K; }
    return Pieces::None;
}

// Uses a vector of type ChessPieces and creates 32 objects which are pushed into that vector
void ChessPieces::create_chess_pieces(std::vector<ChessPieces>& chess_pieces){
        for(int i = 1; i <= 32; i++){
        ChessPieces piece;
        piece.Set_ID(i);
        chess_pieces.push_back(piece);
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
void ChessPieces::set_piece_colors(std::vector<ChessPieces>& chess_pieces){

    sf::Color piece_color = {0,0,255,255};

    for(int i = 0; i < 32; i++){
        
        //Pieces type = get_piece_type(chess_pieces[i].object_id);
        Pieces type = chess_pieces[i].get_piece_type();

        if(chess_pieces[i].object_id <= 16){ piece_color = sf::Color::White; }
        if(chess_pieces[i].object_id > 16 && chess_pieces[i].object_id <= 32){ piece_color = sf::Color::Black; }

        if(type == Pieces::P){ chess_pieces[i].pawn.setFillColor(piece_color);}
        if(type == Pieces::B){ chess_pieces[i].bishop.setFillColor(piece_color);}
        if(type == Pieces::N){ chess_pieces[i].knight.setFillColor(piece_color);}
        if(type == Pieces::R){ chess_pieces[i].rook.setFillColor(piece_color);}
        if(type == Pieces::Q){ chess_pieces[i].queen.setFillColor(piece_color);}
        if(type == Pieces::K){ chess_pieces[i].king.setFillColor(piece_color);}

    }
}

// Set initial piece positions
void ChessPieces::place_pieces(std::vector<ChessPieces>& chess_pieces){

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            // note that the object id returned from map_value is an abstract version not the class version
            int map_value = piece_map_v2[y][x]; // an objects id at a started position position ex:{0, 0}
            Pieces type = chess_pieces[map_value-1].get_piece_type(); // type of piece that object id is

            if(type == Pieces::P){chess_pieces[map_value-1].pawn.setPosition(square_map[y][x].first, square_map[y][x].second);}
            if(type == Pieces::B) { chess_pieces[map_value-1].bishop.setPosition(square_map[y][x].first, square_map[y][x].second);}
            if(type == Pieces::N) { chess_pieces[map_value-1].knight.setPosition(square_map[y][x].first, square_map[y][x].second);}
            if(type == Pieces::R) { chess_pieces[map_value-1].rook.setPosition(square_map[y][x].first, square_map[y][x].second);}
            if(type == Pieces::Q) { chess_pieces[map_value-1].queen.setPosition(square_map[y][x].first, square_map[y][x].second);}
            if(type == Pieces::K) { chess_pieces[map_value-1].king.setPosition(square_map[y][x].first, square_map[y][x].second);}

        }
    }
}

// Draws all pieces
void ChessPieces::render_pieces(ChessboardWindow& window, std::vector<ChessPieces>& chess_pieces){

    for(int i = 0; i < 32; i++){

    //Pieces type = get_piece_type(chess_pieces[i].object_id);
    Pieces type = chess_pieces[i].get_piece_type();

    if(type == Pieces::P) { window.getWindow().draw(chess_pieces[i].pawn);}
    if(type == Pieces::B) { window.getWindow().draw(chess_pieces[i].bishop);}
    if(type == Pieces::N) { window.getWindow().draw(chess_pieces[i].knight);}
    if(type == Pieces::R) { window.getWindow().draw(chess_pieces[i].rook);}
    if(type == Pieces::Q) { window.getWindow().draw(chess_pieces[i].queen);}
    if(type == Pieces::K) { window.getWindow().draw(chess_pieces[i].king);}

    }
}

// Use to setup initial chess board with pieces, sets colors, places pieces, render and display them
void ChessPieces::setup_pieces(ChessboardWindow& window, std::vector<ChessPieces>& chess_pieces){
    set_piece_colors(chess_pieces);
    place_pieces(chess_pieces);
    render_pieces(window, chess_pieces);
    window.getWindow().display();
}

// Returns player piece selection or piece destination when using true
ChessPieces::Selection ChessPieces::select_piece(bool destination){

    ChessPieces::Selection selection;
    std::string input_move;

    select_piece:
    if(!destination){ std::cout << "Select a piece - Ex: Ba7, a6, Ne4\n";}
    else{std::cout << "Select a destination\n";}
    std::cin >> input_move; // should be some form of Ba7 or a6

    if(input_move.length() == 2){ // for pawns
        selection.piece_type = 0;
        selection.letter = static_cast<int>(letter_notation_map.at(input_move[0]));
        selection.number = input_move[1] - '0';
    }
    else if(input_move.length() == 3){ // for pieces
        selection.piece_type = static_cast<int>(piece_notation_map.at(input_move[0]));
        selection.letter = static_cast<int>(letter_notation_map.at(input_move[1]));
        selection.number = input_move[2] - '0'; // -'0' converts 0-9 char to numeral
    }
    else{ std::cout << "Not a valid piece" << std::endl; goto select_piece;}

    return selection;
}


// void ChessPieces::move_piece(ChessboardWindow& window, Chessboard& board){

//     ChessPieces::Selection selection_input = select_piece(false);
//     ChessPieces::Selection destination_input = select_piece(true);

//     // If playing as white - need to invert number, can keep letter same, if black then opposite
//     int invert_num = (8 - destination_input.number) + 1;
//     int number = invert_num - 1; // -1 for array
//     int letter = destination_input.letter - 1;

//     // selected piece

//     // set piece position

//     board.create(window);
//     // window.getWindow().draw(selected piece); 
//     window.getWindow().display();
//     // render_pieces(window);

// }

/*

  A B C D E F G H
8 0 0 0 0 0 0 0 0 8
7 1 1 1 1 1 1 1 1 7
6 1 1 1 1 1 1 1 1 6
5 1 1 1 1 1 1 1 1 5
4 1 1 1 1 1 1 1 1 4
3 1 1 1 1 1 1 1 1 3
2 1 1 1 1 1 1 1 1 2
1 0 0 0 0 0 0 0 0 1
  A B C D E F G H

Move storage - reverse moves 
King state - checks / checkmate / stalemate
-8 +8 check in front behind
-1 +1 check left right
-8-1 -8+1, +8+1 +8-1, diagonals
bounds check?

*/

/*
Takes input: a6->a7, Bb7, Ne4, Ke8->Kd7
Stores input: Go back left arrow 

Chess Rules Basic:
- take input: Ra6->Ra8  -- Rook at [6][a] to [8][a]
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

- If obstruction found check if white or black
- If opposite color and piece can attack then take piece and stop there

Piece rules:
-Limit spaces able to move and direction of movement(how?)


Set piece: set piece to new spot clear spot if necessary


// Returns a chess piece of type CircleShape
// sf::CircleShape& ChessPieces::get_piece_basic(int piece_type){
//     switch (piece_type){
//     case 1: return pawn; break;   case 2: return bishop; break;
//     case 3: return knight; break; case 4: return rook; break;
//     case 5: return queen; break;  case 6: return king; break;
//     default: return null; break; }
// }

*/