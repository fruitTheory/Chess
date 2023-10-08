#include "SFML/Graphics.hpp"
#include "chess_window.hpp"
#include "chess_pieces.hpp"
#include "chess_board.hpp"
#include "config.hpp"
#include <iostream>


int main(){

    ChessboardWindow window; // window object
    Chessboard board; // board object
    board.create(window);
    
    ChessPieces piece;
    sf::CircleShape& pawn = piece.get_piece(PieceType::PAWN);

    // set piece original positions
    for(int i = 0; i < 8; i++){
            pawn.setPosition(96 * i, (96 * 6) + 8);
            window.getWindow().draw(pawn);
    }
    // for(int i = 0; i < 2; i++){
    //         pawn.setPosition(96 * (i * 6), (96 * 7) + 8);
    //         window.getWindow().draw(rook);
    // }

    // main loop
    sf::Event event;
    while (window.getWindow().isOpen()){
        while (window.getWindow().pollEvent(event))
            if (event.type == sf::Event::Closed){ window.getWindow().close();; }
        
        window.getWindow().display();;
    }

    return EXIT_SUCCESS;
}