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

    // set piece original positions
    for(int i = 0; i < 8; i++){
            pawn.setPosition(96 * i, (96 * 6) + 8);
            window.getWindow().draw(pawn);
    }

    rook.setPosition(20, 20);
    rook.setOrigin(24, 24);
    rook.rotate(90);
    window.getWindow().draw(rook);
    window.getWindow().display(); // display window

    // extern int window_width; extern int window_height;
    
    sf::Event event;
    while (window.getWindow().isOpen()){
        while (window.getWindow().pollEvent(event))
            if (event.type == sf::Event::Closed){ window.getWindow().close(); }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i localPosition = mouse_click_position(window);
            if(localPosition.x > 0 && localPosition.y > 0){
                std::cout << "Clicked\n";
                std::cout << localPosition.x << " " << localPosition.y << std::endl;
            }
        }
    }

    return EXIT_SUCCESS;
}

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