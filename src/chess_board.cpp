#include "chess_board.hpp"
#include "chessboard_window.hpp"
#include <iostream>


// A map of X and Y pairs that uses top left value of 96 unit(size) squares
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

Chessboard::Chessboard():
dark_square_color(0,45,85,255),
light_square_color(185,195,205,255),
board_square_size(96.f, 96.f) 
{

}

// Clear window and create board
void Chessboard::create(ChessboardWindow& window){

    // int light square
    sf::RectangleShape dark_square(board_square_size);
    dark_square.setFillColor(dark_square_color);
    
    // int light square
    sf::RectangleShape light_square(board_square_size);
    light_square.setFillColor(light_square_color);

    /*
    Sets light and dark squares based on odd or even
    To flip board make modulus !not even, and swap +offsets -offsets
    */
    int offset = 0;
    int flop = 0;
    for(int y = 0; y < 8; y++){
        if(flop == 1){offset = 1;} else {offset = 0;}
        for(int x = 0; x < 8; x++){
            if(x % 2 == 0){
                light_square.setPosition(square_map[y][x+offset].first, square_map[y][x+offset].second);
                window.getWindow().draw(light_square);
            } 
            else{
            dark_square.setPosition(square_map[y][x-offset].first, square_map[y][x-offset].second);
            window.getWindow().draw(dark_square);
            }
        }
        window.getWindow().display();
        window.getWindow().isOpen();
        flop ^= 1;
    }

    window.getWindow().display();
    
}

