#include "SFML/Graphics.hpp"
#include "chess_window.hpp"
#include "chess_pieces.hpp"
#include "chess_board.hpp"
#include "config.hpp"
#include <iostream>

sf::Vector2i mouse_click_position(ChessboardWindow& window);

int main(){

    ChessboardWindow window; // window object
    Chessboard board; // board object
    board.create(window);
    
    ChessPieces piece;
    sf::CircleShape& pawn = piece.get_piece(PieceType::PAWN);
    sf::CircleShape& rook = piece.get_piece(PieceType::ROOK);

    sf::CircleShape& A2_pawn = piece.get_piece(PieceType::PAWN);
    A2_pawn.setPosition(0, 576);
    window.getWindow().draw(A2_pawn);

    sf::CircleShape& B2_pawn = piece.get_piece(PieceType::PAWN);
    B2_pawn.setPosition(96, 576);
    window.getWindow().draw(B2_pawn);

    window.getWindow().display(); // display window

    bool pressed;
    
    sf::Event event;

    while (window.getWindow().isOpen()){
        while (window.getWindow().pollEvent(event))
            if (event.type == sf::Event::Closed){ window.getWindow().close(); }

        
        pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (pressed){
            sf::Vector2i localPosition = mouse_click_position(window);
            if(localPosition.x > 0 && localPosition.y > 0){
                std::cout << "Clicked\n";
                std::cout << localPosition.x << " " << localPosition.y << std::endl;
                board.create(window);

                sf::CircleShape& B2_pawn = piece.get_piece(PieceType::PAWN);
                B2_pawn.setPosition(96, 576);
                window.getWindow().draw(B2_pawn);

                // set position of object to cursor position offset by size of object to center
                A2_pawn.setPosition(localPosition.x-48, localPosition.y-48);
                window.getWindow().draw(A2_pawn);
                window.getWindow().display();

            }
            
        }
    }

    return EXIT_SUCCESS;
}

/*
Will probably need to store state of board pieces to redraw
*/

sf::Vector2i mouse_click_position(ChessboardWindow& window){

        extern int window_width; extern int window_height;

        sf::Vector2i localPosition = sf::Mouse::getPosition(window.getWindow());
        if(localPosition.x >= 0 && localPosition.x <= window_width && 
           localPosition.y >= 0 && localPosition.y <= window_height){
                return localPosition;
        }
        sf::Vector2i fail = {-1, -1};
        return fail; // out of bounds
}