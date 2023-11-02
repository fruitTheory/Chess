#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"
#include "chess_pieces.hpp"
#include "chess_board.hpp"
#include "chess_utility.hpp"
#include "chess_clock.hpp"
#include "chess_mouse.hpp"
#include "chess_text.hpp"
#include "chess_history.hpp"
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
    std::string user_input; // users move input
    std::thread clock_thread(start_internal_clock); // create thread for timer function
    std::cout << "Select a piece and destination - Ex: c1 f4, c2 c4 \n";

    while ( window.isOpen() ){
        while ( window.pollEvent(event) ){
            switch( event.type ){

                // Window close
                case sf::Event::Closed :{
                    window.close();
                    goto exit;
                    break;
                }

                // Mouse pressed
                case sf::Event::MouseButtonPressed :{
                    pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
                    if (pressed){
                        sf::Vector2i mouse_position = mouse_click_position(window);
                        if(mouse_position.x > 0 && mouse_position.y > 0){
                            std::cout << "Clicked\n";
                            std::cout << mouse_position.x << " " << mouse_position.y << std::endl;
                        }
                    }
                    break;
                }

                // Text entered
                case sf::Event::TextEntered :{

                    // Unicode 13 represents Enter
                    if (event.text.unicode == 13){
                        flop == 1 ? player = chess_pieces.WHITE : player = chess_pieces.BLACK;
                        piece_moved = chess_pieces.move_piece(window, board, chess_pieces, pieces, player, user_input);
                        if(piece_moved){ flop ^= 1; }
                        user_input = "";
                    }
                    // Unicode 8 represents Backspace
                    else if (event.text.unicode == 8 && user_input.size() > 0){
                        user_input.pop_back();
                    }
                    // Unicode < 128 is Latin alphabet and ASCII symbols
                    else if (event.text.unicode < 128 && event.text.unicode != 8){
                        user_input += static_cast<char>(event.text.unicode);
                    }
                    // std::cout << user_input << std::endl;
                    break;
                }

                // Default
                default :{
                    break;
                }

            }
        }

        // Default update and draw display
        window.clear();
        chess_pieces.update_pieces(window, board, pieces);
        draw_clock_display(window);
        draw_textbox(window, user_input);
        window.display();
    }

    clock_thread.join();
    exit:
    clock_thread.detach();
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