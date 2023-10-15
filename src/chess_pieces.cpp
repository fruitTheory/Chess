#include "chess_pieces.hpp"
#include "chess_utility.hpp"
#include <iostream>
#include <utility>

// storage of created shapes(pieces)
sf::CircleShape piece[64];

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

// Map for piece placement
int piece_map[64] = 
{
    4, 2, 3, 5, 6, 3, 2, 4,
    1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    4, 2, 3, 5, 6, 3, 2, 4
};

// Map for piece color placement
int color_map[64] = 
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2
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

// Returns a chess piece of type CircleShape
// sf::CircleShape& ChessPieces::get_piece_basic(int piece_type){
//     switch (piece_type){
//     case 1: return pawn; break;   case 2: return bishop; break;
//     case 3: return knight; break; case 4: return rook; break;
//     case 5: return queen; break;  case 6: return king; break;
//     default: return null; break; }
// }

void ChessPieces::Set_ID(int ID){ object_id = ID; }
int ChessPieces::Get_ID(){ return object_id; }

// returns piece type of shape
sf::CircleShape ChessPieces::get_piece_type(){ return piece_type; }

// Takes a vector of type ChessPieces and creates 32 objects which are pushed into that vector
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
    // white_king     : 15          // black_king     : 31
    // white_queen    : 16          // black_queen    : 32    

    */

// Takes a vector of type ChessPieces
void ChessPieces::draw_pieces(ChessboardWindow& window, std::vector<ChessPieces>& chess_pieces){

    for(int i = 0; i < 32; i++){

        // set white pawns 1 to 8
        if(chess_pieces[i].object_id <= 8){
            chess_pieces[i].pawn.setPosition(square_map[6][i].first, square_map[6][i].second);
            window.getWindow().draw(chess_pieces[i].pawn);
        }
        // set white bishops 9, 10
        if(chess_pieces[i].object_id == 9){
            chess_pieces[i].bishop.setPosition(square_map[7][2].first, square_map[7][2].second);
            window.getWindow().draw(chess_pieces[i].bishop);
        }
        if(chess_pieces[i].object_id == 10){
            chess_pieces[i].bishop.setPosition(square_map[7][5].first, square_map[7][5].second);
            window.getWindow().draw(chess_pieces[i].bishop);
        }
        // set white knights 11, 12
        if(chess_pieces[i].object_id == 11){
            chess_pieces[i].knight.setPosition(square_map[7][1].first, square_map[7][1].second);
            window.getWindow().draw(chess_pieces[i].knight);
        }
        if(chess_pieces[i].object_id == 12){
            chess_pieces[i].knight.setPosition(square_map[7][6].first, square_map[7][6].second);
            window.getWindow().draw(chess_pieces[i].knight);
        }
        // set white rooks 13, 14
        if(chess_pieces[i].object_id == 13){
            chess_pieces[i].rook.setPosition(square_map[7][0].first, square_map[7][0].second);
            window.getWindow().draw(chess_pieces[i].rook);
        }
        if(chess_pieces[i].object_id == 14){
            chess_pieces[i].rook.setPosition(square_map[7][7].first, square_map[7][7].second);
            window.getWindow().draw(chess_pieces[i].rook);
        }
        // set white queen 5
        if(chess_pieces[i].object_id == 15){
            chess_pieces[i].queen.setPosition(square_map[7][3].first, square_map[7][3].second);
            window.getWindow().draw(chess_pieces[i].queen);
        }
        // set white king 6
        if(chess_pieces[i].object_id == 16){
            chess_pieces[i].king.setPosition(square_map[7][4].first, square_map[7][4].second);
            window.getWindow().draw(chess_pieces[i].king);
        }
        // set white piece colors
        if(chess_pieces[i].object_id <= 16){
            chess_pieces[i].pawn.setFillColor(sf::Color::Black);
            chess_pieces[i].bishop.setFillColor(sf::Color::Black);
            chess_pieces[i].knight.setFillColor(sf::Color::Black);
            chess_pieces[i].queen.setFillColor(sf::Color::Black);
            chess_pieces[i].king.setFillColor(sf::Color::Black);
            // window.getWindow().draw(chess_pieces[i].pawn);
            // window.getWindow().draw(chess_pieces[i].bishop);
            // window.getWindow().draw(chess_pieces[i].knight);
        }

        // set black pawns
        if(chess_pieces[i].object_id > 16 && chess_pieces[i].object_id <= 24){
            chess_pieces[i].pawn.setPosition(square_map[1][i-16].first, square_map[1][i-16].second);
            chess_pieces[i].pawn.setFillColor(sf::Color::Black);
            window.getWindow().draw(chess_pieces[i].pawn);
        }

        int black_y = 0;
        // set black bishops 25, 26
        if(chess_pieces[i].object_id == 25){
            chess_pieces[i].bishop.setPosition(square_map[black_y][2].first, square_map[black_y][2].second);
            chess_pieces[i].bishop.setFillColor(sf::Color::Black);
            window.getWindow().draw(chess_pieces[i].bishop);
        }

        if(chess_pieces[i].object_id == 26){
            chess_pieces[i].bishop.setPosition(square_map[black_y][5].first, square_map[black_y][5].second);
            chess_pieces[i].bishop.setFillColor(sf::Color::Black);
            window.getWindow().draw(chess_pieces[i].bishop);
        }

        // set black knights 27, 28
        if(chess_pieces[i].object_id == 27){
            chess_pieces[i].knight.setPosition(square_map[black_y][1].first, square_map[black_y][1].second);
            chess_pieces[i].knight.setFillColor(sf::Color::Black);
            window.getWindow().draw(chess_pieces[i].knight);
        }
        if(chess_pieces[i].object_id == 28){
            chess_pieces[i].knight.setPosition(square_map[black_y][6].first, square_map[black_y][6].second);
            chess_pieces[i].knight.setFillColor(sf::Color::Black);
            window.getWindow().draw(chess_pieces[i].knight);
        }

        // set black rooks 29, 30
        if(chess_pieces[i].object_id == 29){
            chess_pieces[i].rook.setPosition(square_map[black_y][0].first, square_map[black_y][0].second);
            chess_pieces[i].rook.setFillColor(sf::Color::Black);
            window.getWindow().draw(chess_pieces[i].rook);
        }
        if(chess_pieces[i].object_id == 30){
            chess_pieces[i].rook.setPosition(square_map[black_y][7].first, square_map[black_y][7].second);
            chess_pieces[i].rook.setFillColor(sf::Color::Black);
            window.getWindow().draw(chess_pieces[i].rook);
        }

        // set black queen 31
        if(chess_pieces[i].object_id == 31){
            chess_pieces[i].queen.setPosition(square_map[black_y][3].first, square_map[black_y][3].second);
            chess_pieces[i].queen.setFillColor(sf::Color::Black);
            window.getWindow().draw(chess_pieces[i].queen);
        }

        // set black king 32
        if(chess_pieces[i].object_id == 32){
            chess_pieces[i].king.setPosition(square_map[black_y][4].first, square_map[black_y][4].second);
            chess_pieces[i].king.setFillColor(sf::Color::Black);
            window.getWindow().draw(chess_pieces[i].king);
        }

        // set black piece colors
        if(chess_pieces[i].object_id > 16 || chess_pieces[i].object_id <= 32){
            chess_pieces[i].king.setFillColor(sf::Color::Black);
        }

    }

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

    if(input_move.length() == 3){ // for pieces
        selection.piece_type = static_cast<int>(piece_notation_map.at(input_move[0]));
        selection.letter = static_cast<int>(letter_notation_map.at(input_move[1]));
        selection.number = input_move[2] - '0'; // -'0' converts 0-9 char to numeral
        std::cout << selection.piece_type << std::endl;
        std::cout << selection.letter << std::endl;
        std::cout <<  selection.number << std::endl;
    }
    else if(input_move.length() == 2){ // for pawns
        selection.piece_type = 0;
        selection.letter = static_cast<int>(letter_notation_map.at(input_move[0]));
        selection.number = input_move[1] - '0'; 
        std::cout << selection.letter << std::endl;
        std::cout <<  selection.number << std::endl;
    }
    else{ std::cout << "Not a valid piece" << std::endl; goto select_piece;}

    return selection;
}


void ChessPieces::set_piece(ChessboardWindow& window, Chessboard& board){

    ChessPieces::Selection selection_input = select_piece(false);
    ChessPieces::Selection destination_input = select_piece(true);

    // If playing as white - need to invert number, can keep letter same, if black then opposite
    int invert_num = (8 - destination_input.number) + 1;
    int number = invert_num - 1; // -1 for array
    int letter = destination_input.letter - 1;

    sf::CircleShape selected_piece = piece[0];

    // set piece position
    selected_piece.setPosition(square_map[number][letter].first, square_map[number][letter].second);

    // piece_map[0] = 0; // clears piece
    // piece_map[42] = 4; // overwrite piece in posiiton
    // color_map[42] = color_map[0]; // set color to previous

    board.create(window);
    window.getWindow().draw(selected_piece); 
    window.getWindow().display();
    // draw_pieces(window);

}

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

*/