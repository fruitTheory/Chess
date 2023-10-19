#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"
#include "chess_pieces.hpp"
#include "chess_board.hpp"
#include "chess_utility.hpp"
#include "config.hpp"
#include <iostream>
#include <thread>


int main(){

    ChessboardWindow window; // window object
    Chessboard board; // board object
    ChessPieces chess_pieces; // chess pieces object
    std::vector<ChessPieces> pieces; // array for piece objects

    chess_pieces.create_chess_pieces(pieces);
    chess_pieces.setup_pieces(window, board, pieces);
    
    std::thread timer_thread(game_clock, std::ref(window)); // passing function pointer to timer thread

    bool piece_moved;
    bool pressed = false;
    sf::Event event;

    while (window.getWindow().isOpen()){
        while (window.getWindow().pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.getWindow().close(); } 
        }

        // if(!piece_moved){piece_moved = chess_pieces.move_piece(window, board, pieces);}
        piece_moved = chess_pieces.move_piece(window, board, pieces);

        pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (pressed){
            sf::Vector2i mouse_position = mouse_click_position(window);
            if(mouse_position.x > 0 && mouse_position.y > 0){

                std::cout << "Clicked\n";
                std::cout << mouse_position.x << " " << mouse_position.y << std::endl;

                // reset_board(window, board, pieces);
                
                // get piece from chess pieces
                // sf::CircleShape& A2_pawn = chess_pieces.get_piece_basic(1);
                // board.create(window);
                // // set position of object to cursor position offset by size of object to center
                // A2_pawn.setPosition(mouse_position.x-48, mouse_position.y-48);
                // window.getWindow().draw(A2_pawn);
                // chess_pieces.init_piece_position(window);
            }
        // piece_moved = false;
        timer_thread.join();
        }
    }
    window.getWindow().display();
    return EXIT_SUCCESS;
}
