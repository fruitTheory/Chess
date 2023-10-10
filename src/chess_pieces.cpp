#include "chess_pieces.hpp"
#include <iostream>
#include <utility>

ChessPieces::ChessPieces():
null(0.f, 3),
pawn(48.f, 3),
knight(48.f, 5),
bishop(48.f, 4),
rook(48.f, 6),
king(48.f, 8),
queen(48.f, 100)
{

}

// 48 unit size piece
sf::CircleShape& ChessPieces::get_piece(int piece_type){
    switch (piece_type)
    {
    case 1: return pawn; break;
    case 2: return knight; break;
    case 3: return bishop; break;
    case 4: return rook; break;
    case 5: return king; break;
    case 6: return queen; break;
    default:
        return null;
        break;
    }
}

// Map for piece placement
const int piece_map[64] = 
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
const int piece_color_map[64] = 
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

// Map always using top left values of 96 unit(size) squares
const std::pair<int, int> square_map[8][8] = {
    {{0, 0},   {96, 0},   {192, 0},   {288, 0},   {384, 0},   {480, 0},   {576, 0},   {672, 0}},
    {{0, 96},  {96, 96},  {192, 96},  {288, 96},  {384, 96},  {480, 96},  {576, 96},  {672, 96}},
    {{0, 192}, {96, 192}, {192, 192}, {288, 192}, {384, 192}, {480, 192}, {576, 192}, {672, 192}},
    {{0, 288}, {96, 288}, {192, 288}, {288, 288}, {384, 288}, {480, 288}, {576, 288}, {672, 288}},
    {{0, 384}, {96, 384}, {192, 384}, {288, 384}, {384, 384}, {480, 384}, {576, 384}, {672, 384}},
    {{0, 480}, {96, 480}, {192, 480}, {288, 480}, {384, 480}, {480, 480}, {576, 480}, {672, 480}},
    {{0, 576}, {96, 576}, {192, 576}, {288, 576}, {384, 576}, {480, 576}, {576, 576}, {672, 576}},
    {{0, 672}, {96, 672}, {192, 672}, {288, 672}, {384, 672}, {480, 672}, {576, 672}, {672, 672}}
};

// General Notation mapping
std::pair<Letters, int> notation_map[8][8] = {
    {{a, 8}, {b, 8}, {c, 8}, {d, 8}, {e, 8}, {f, 8}, {g, 8}, {h, 8}},
    {{a, 7}, {b, 7}, {c, 7}, {d, 7}, {e, 7}, {f, 7}, {g, 7}, {h, 7}},
    {{a, 6}, {b, 6}, {c, 6}, {d, 6}, {e, 6}, {f, 6}, {g, 6}, {h, 6}},
    {{a, 5}, {b, 5}, {c, 5}, {d, 5}, {e, 5}, {f, 5}, {g, 5}, {h, 5}},
    {{a, 4}, {b, 4}, {c, 4}, {d, 4}, {e, 4}, {f, 4}, {g, 4}, {h, 4}},
    {{a, 3}, {b, 3}, {c, 3}, {d, 3}, {e, 3}, {f, 3}, {g, 3}, {h, 3}},
    {{a, 2}, {b, 2}, {c, 2}, {d, 2}, {e, 2}, {f, 2}, {g, 2}, {h, 2}},
    {{a, 1}, {b, 1}, {c, 1}, {d, 1}, {e, 1}, {f, 1}, {g, 1}, {h, 1}},
};

// Letter notations mapping
std::map<char, Letters> letter_notation_map = {
    {'a', a},{'b', b},{'c', c},{'d', d},
    {'e', e},{'f', f},{'g', g},{'h', h}
};

// Piece notations mapping
std::map<char, Pieces> piece_notation_map = {
    {'N', N},{'B', B},{'R', R},{'Q', Q},{'K', K}
};

// Set pieces on board in default places
void ChessPieces::initialize_piece_position(ChessboardWindow& window){

    sf::CircleShape piece[64];
    int num = 0;

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            piece[num] = ChessPieces::get_piece(piece_map[num]);
            piece[num].setPosition(square_map[y][x].first, square_map[y][x].second);
            if(piece_color_map[num] == 1){ piece[num].setFillColor(sf::Color::Black); }
            if(piece_color_map[num] == 2){ piece[num].setFillColor(sf::Color::White); }
            window.getWindow().draw(piece[num]);
            num++;
        }
    }

}

// Basic move pieces
void ChessPieces::move_piece_basic(){

    int input_piece = 0;
    int input_letter = 0;
    int input_number = 0;

    std::string input_move;
    std::cout << "Make a move\n";
    std::cin >> input_move; // should be some form of Ba7 or a6

    if(input_move.length() == 3){ // for pieces
        input_piece = piece_notation_map[input_move[0]];
        input_letter = letter_notation_map[input_move[1]];
        input_number = input_move[2] - '0'; 
        std::cout << input_piece << std::endl;
        std::cout << input_letter << std::endl;
        std::cout << input_number << std::endl;
    }
    else if(input_move.length() == 2){ // for pawns
        input_piece = 0;
        input_letter = letter_notation_map[input_move[0]];
        input_number = input_move[1] - '0'; // -'0' converts 0-9 char to numeral
        std::cout << input_letter << std::endl;
        std::cout << input_number << std::endl;
    }


}

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

*/