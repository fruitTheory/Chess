#include "chess_board.hpp"
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

// Setup board squares and notation helper
void Chessboard::create(sf::RenderWindow& window){

    sf::RectangleShape dark_square(board_square_size);
    dark_square.setFillColor(dark_square_color);
    
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
                window.draw(light_square);
            } 
            else{
                dark_square.setPosition(square_map[y][x-offset].first, square_map[y][x-offset].second);
                window.draw(dark_square);
            }
        }
        flop ^= 1;
    }

    create_notation_helper(window);
    
}

void Chessboard::create_notation_helper(sf::RenderWindow& window){
    
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("./font/DejaVuSans.ttf")){puts("Didnt load .ttf");}
    
    const char temp_letters[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    const char temp_numbers[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};

    // Use -x to flip board
    text.setFont(font);
    text.setCharacterSize(14);
    text.setFillColor(light_square_color);

    // Create letter notation
    for(int x = 0; x < 8; x++){
        text.setString(temp_letters[x]);
        text.setPosition((x * 96) + 2, 768);
        window.draw(text);
    }

    // Create number notation
    for(int x = 0; x < 8; x++){
        text.setString(temp_numbers[x]);
        text.setPosition(768 + 3, 672 - (x * 96) + 2);
        window.draw(text);
    }
    
}