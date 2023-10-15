#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"
#include "chess_pieces.hpp"
#include "chess_board.hpp"
#include "chess_utility.hpp"
#include "config.hpp"
#include <iostream>


int main(){

    ChessboardWindow window; // window object
    Chessboard board; // board object
    ChessPieces chess_pieces; // chess pieces object

    board.create(window);

    std::vector<ChessPieces> pieces;
    chess_pieces.create_chess_pieces(pieces);

    chess_pieces.setup_pieces(window, pieces);
    chess_pieces.move_piece(window, board);

    bool pressed = false;
    sf::Event event;

    while (window.getWindow().isOpen()){
        while (window.getWindow().pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.getWindow().close(); } }

        pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (pressed){

            sf::Vector2i mouse_position = mouse_click_position(window);

            if(mouse_position.x > 0 && mouse_position.y > 0){

                std::cout << "Clicked\n";
                std::cout << mouse_position.x << " " << mouse_position.y << std::endl;

                // get piece from chess pieces
                // sf::CircleShape& A2_pawn = chess_pieces.get_piece_basic(1);
                // board.create(window);
                // // set position of object to cursor position offset by size of object to center
                // A2_pawn.setPosition(mouse_position.x-48, mouse_position.y-48);
                // window.getWindow().draw(A2_pawn); // hard code redraw pawn
                // chess_pieces.init_piece_position(window);
            }

        window.getWindow().display();
            
        }
    }

    return EXIT_SUCCESS;
}
