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


const std::pair<int, int> square_map[8][8] = {
    {{0, 0}, {96, 0}, {192, 0}, {288, 0}, {384, 0}, {480, 0}, {576, 0}, {672, 0}},
    {{0, 96}, {96, 96}, {192, 96}, {288, 96}, {384, 96}, {480, 96}, {576, 96}, {672, 96}},
    {{0, 192}, {96, 192}, {192, 192}, {288, 192}, {384, 192}, {480, 192}, {576, 192}, {672, 192}},
    {{0, 288}, {96, 288}, {192, 288}, {288, 288}, {384, 288}, {480, 288}, {576, 288}, {672, 288}},
    {{0, 384}, {96, 384}, {192, 384}, {288, 384}, {384, 384}, {480, 384}, {576, 384}, {672, 384}},
    {{0, 480}, {96, 480}, {192, 480}, {288, 480}, {384, 480}, {480, 480}, {576, 480}, {672, 480}},
    {{0, 576}, {96, 576}, {192, 576}, {288, 576}, {384, 576}, {480, 576}, {576, 576}, {672, 576}},
    {{0, 672}, {96, 672}, {192, 672}, {288, 672}, {384, 672}, {480, 672}, {576, 672}, {672, 672}}
};

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
