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
sf::CircleShape& ChessPieces::get_piece_basic(int piece_type){
    switch (piece_type){
    case 1: return pawn; break;   case 2: return bishop; break;
    case 3: return knight; break; case 4: return rook; break;
    case 5: return queen; break;  case 6: return king; break;
    default: return null; break; }
}

// Set pieces on board in default places - Updates draw
void ChessPieces::draw_pieces(ChessboardWindow& window){

    // Pieces pawn;
    // Pieces::P;
    // Pieces::B;

    // piece[num].setPosition(square_map[y][x].first, square_map[y][x].second);

    int num = 0;
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            piece[num] = ChessPieces::get_piece_basic(piece_map[num]);
            piece[num].setPosition(square_map[y][x].first, square_map[y][x].second);
            if(color_map[num] == 1){ piece[num].setFillColor(sf::Color::Black); }
            if(color_map[num] == 2){ piece[num].setFillColor(sf::Color::White); }
            window.getWindow().draw(piece[num]); 
            num++;
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

    //B -- a 7 --  8 x 8 -- 64 

    int number = destination_input.number;
    int letter = destination_input.letter;

    sf::CircleShape selected_piece = piece[0];
    selected_piece.setPosition(square_map[number][letter].first, square_map[number][letter].second);

    // piece_map[0] = 0; // clears piece
    // piece_map[42] = 4; // overwrite piece in posiiton
    // color_map[42] = color_map[0]; // set color to previous

    board.create(window);
    // window.getWindow().draw(selected_piece); 
    // window.getWindow().display();
    draw_pieces(window);

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