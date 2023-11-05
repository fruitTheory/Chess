#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"
#include "chess_pieces.hpp"
#include "chess_board.hpp"
#include "chess_utility.hpp"
#include "chess_clock.hpp"
#include "chess_mouse.hpp"
#include "chess_text.hpp"
#include "chess_history.hpp"
#include "chess_sprites.hpp"
#include <iostream>
#include <thread>


int main(){

    sf::RenderWindow window;
    Chessboard board; // board object
    ChessPieces chess_pieces; // chess pieces object
    std::vector<ChessPieces> pieces; // array for piece objects
    ChessPieces::Move move;
    ChessUtility utils;

    chess_pieces.create_chess_pieces(pieces);
    initialize_window(window);
    initialize_render(window, board, chess_pieces, pieces);

    bool piece_moved;
    bool pressed = false;
    bool pressed_twice = false;
    int press_count = 0;

    sf::Event event;
    std::string user_input; // users move input
    std::thread clock_thread(start_internal_clock); // create thread for timer function
    puts("Select a piece and destination - Ex: c1 f4, c2 c4");

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
                    press_count += 1;
                    sf::Vector2i mouse_position = get_mouse_position(window);
                    
                    if (pressed && press_count == 1){
                        // first click get move
                        if(mouse_position.x > 0 && mouse_position.y > 0){
                            move.start = move_from_click(board, mouse_position);
                            move.end = {Pieces::None, -1, -1, -1, -1};
                            utils.check_turn();
                        }
                    }

                    // second click get move
                    if(pressed && press_count == 2){
                        move.end = move_from_click(board, mouse_position);
                        utils.check_turn();
                        std::cout << press_count << std::endl;
                        piece_moved = chess_pieces.move_piece(window, board, chess_pieces, pieces, move);
                        if(piece_moved){ 
                            players_turn ^= 1;
                        }
                        press_count = 0;
                        std::cout << move.start.letter << " " << move.start.number << std::endl;
                        std::cout << move.end.letter << " " << move.end.number << std::endl;
                    }
                    break;

                }

                // Text entered
                case sf::Event::TextEntered :{

                    // Unicode 13 represents Enter
                    if (event.text.unicode == 13){

                        utils.check_turn();

                        // Check if user input is valid, then allow move piece
                        if(utils.user_input_valid(user_input)){
                            move = utils.convert_user_input(user_input);
                            piece_moved = chess_pieces.move_piece(window, board, chess_pieces, pieces, move);
                        } else { piece_moved = false; }
                        std::cout << piece_moved << std::endl;

                        if(piece_moved){ players_turn ^= 1; }//else{ players_turn = 1;}
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
        //std::cout << players_turn << std::endl;
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