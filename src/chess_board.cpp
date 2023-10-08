#include "chess_board.hpp"
#include "chess_window.hpp"

Chessboard::Chessboard():
base_color(185,195,205,255),
square_color(0,45,85,255),
//highlight_color()
board_square_size(96.f, 96.f) 
{
    // other initializers
}

void Chessboard::create(ChessboardWindow& window){
    
    base_color + square_color;
    window.getWindow().clear(base_color); // initial color
    sf::RectangleShape board_square(board_square_size);
    board_square.setFillColor(square_color);

    // set board up
    int flop = 0;
    for(int y = 0; y < 8; y++){
        int current_y = y * 96;
        for(int i = 0; i < 5; i++){
            window.getWindow().draw(board_square);
            if(!flop)
                board_square.setPosition((192 * i), current_y);
            if(flop)
                board_square.setPosition((192 * i) + 96, current_y);
        }
        flop ^= 1;
    }

}
