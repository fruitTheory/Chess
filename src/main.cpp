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
    board.create(window); // create board
    
    ChessPieces chess_pieces; // chess piece object

    // get piece from chess pieces
    sf::CircleShape& A2_pawn = chess_pieces.get_piece(1);

    chess_pieces.initialize_piece_position(window); // initial pieces
    window.getWindow().display(); // display window initially

    // init vars
    bool pressed = false;
    sf::Event event;
    chess_pieces.move_piece_basic();
    while (window.getWindow().isOpen()){
        while (window.getWindow().pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.getWindow().close(); } }

        // on pressed stuff
        pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (pressed){

            sf::Vector2i mouse_position = mouse_click_position(window);

            if(mouse_position.x > 0 && mouse_position.y > 0){

                std::cout << "Clicked\n";
                std::cout << mouse_position.x << " " << mouse_position.y << std::endl;
                board.create(window);

                // set position of object to cursor position offset by size of object to center
                A2_pawn.setPosition(mouse_position.x-48, mouse_position.y-48);
                window.getWindow().draw(A2_pawn); // hard code redraw pawn
                chess_pieces.initialize_piece_position(window);


            }

        window.getWindow().display();
        // sf::Time delayTime = sf::milliseconds(500); // 500 milliseconds or 0.5 seconds
        // sf::sleep(delayTime);
            
        }
    }

    return EXIT_SUCCESS;
}

// Returns mouse position within bounds of window, else returns -1
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

