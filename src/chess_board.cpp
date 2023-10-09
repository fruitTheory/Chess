#include "chess_board.hpp"
#include "chess_window.hpp"
#include <iostream>

Chessboard::Chessboard():
base_color(185,195,205,255),
square_color(0,45,85,255),
//highlight_color()
board_square_size(96.f, 96.f) 
{
    // other initializers
}

// Clear and create board
void Chessboard::create(ChessboardWindow& window){
    
    window.getWindow().clear(base_color); // initial color
    sf::RectangleShape board_square(board_square_size);
    board_square.setFillColor(square_color);

    /* 
    Set board up: 
    board size is 768
    Square size is 96 - used for offsetting 
    4 dark squares - board_size/4 = 192
    to flip board, swap which flop has the offset(+96)
    */

    int flop = 0;
    for(int y = 0; y < 8; y++){
        int current_y = y * 96; // y position
        for(int x = 0; x < 4; x++){
            if(flop == 0){
                board_square.setPosition((192 * x) + 96, current_y);
                window.getWindow().draw(board_square);
                sf::FloatRect test = board_square.getGlobalBounds();
                //std::cout << test.left << " " << test.top << std::endl;
            }
            if(flop == 1){
                board_square.setPosition((192 * x), current_y);
                window.getWindow().draw(board_square);
                sf::FloatRect test = board_square.getGlobalBounds();
                //std::cout << test.left << " - " << test.top << std::endl;
            }
        }
        flop ^= 1;
    }
}

/*  well I probably actually need to create light and dark squares 
    dark_square[8][4]
    light_square[8][4] 
    bounding returns x: 96 y: 0 - first dark square - th
*/