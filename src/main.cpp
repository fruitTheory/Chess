#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"
#include "chess_pieces.hpp"
#include "chess_board.hpp"
#include "chess_utility.hpp"
#include "chess_clock.hpp"
#include "chess_mouse.hpp"
#include <iostream>
#include <thread>


int main(){

    sf::RenderWindow window;
    Chessboard board; // board object
    ChessPieces chess_pieces; // chess pieces object
    std::vector<ChessPieces> pieces; // array for piece objects

    chess_pieces.create_chess_pieces(pieces);
    initialize_window(window);
    initialize_render(window, board, chess_pieces, pieces);

    bool piece_moved;
    bool pressed = false;
    int flop = 1;
    int player = chess_pieces.WHITE;
    sf::Event event;

    std::thread clock_thread(start_internal_clock); // create thread for timer function

    while (window.isOpen()){
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.close(); } 
        }

        window.clear();

        flop == 1 ? player = chess_pieces.WHITE : player = chess_pieces.BLACK;

        // if(!piece_moved){piece_moved = chess_pieces.move_piece(window, board, pieces);}
        piece_moved = chess_pieces.move_piece(window, board, chess_pieces, pieces, player);

        pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (pressed){
            sf::Vector2i mouse_position = mouse_click_position(window);
            if(mouse_position.x > 0 && mouse_position.y > 0){

                std::cout << "Clicked\n";
                std::cout << mouse_position.x << " " << mouse_position.y << std::endl;

            }
        // piece_moved = false;
        }
        flop ^= 1;
        // std::cout << "Out of loop\n";
        window.display();
    }

    clock_thread.join();

    return EXIT_SUCCESS;
}


/*
    -Previous mouse click stuff, from inside if clicked

    // board.reset_board(window, board, pieces);
    
    // get piece from chess pieces
    // sf::CircleShape& A2_pawn = chess_pieces.get_piece_basic(1);
    // board.create(window);
    // // set position of object to cursor position offset by size of object to center
    // A2_pawn.setPosition(mouse_position.x-48, mouse_position.y-48);
    // window.draw(A2_pawn);
    // chess_pieces.init_piece_position(window);
*/