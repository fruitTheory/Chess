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

    bool piece_moved = false;
    int press_count = 0;

    sf::Event event;
    std::string user_input; // users move input
    std::thread white_clock_thread(start_clock_white); // create thread for timer 
    std::thread black_clock_thread(start_clock_black);
    ChessPieces::Move_data move_temporary;
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
                    if(event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right ){

                        sf::Vector2i mouse_position = get_mouse_position(window);
                        press_count += 1;
                        
                        // first click move
                        if (event.mouseButton.button == sf::Mouse::Left && press_count == 1){
                            if(mouse_position.x > 0 && mouse_position.y > 0){
                                utils.change_turn();
                                move.start = move_from_click(board, mouse_position);
                                move.end = {Pieces::None, -1, -1, -1, -1};

                                // create temporary move to confirm data from array is valid
                                move_temporary = chess_pieces.convert_move(move.start, pieces);
                                int piece_id = piece_map[move_temporary.number][move_temporary.letter];

                                // if the selection square is empty or is opposite teams color then clear
                                if(piece_id == 0 
                                || pieces[piece_id-1].Get_Color_ID() != players_turn)
                                { press_count = 0; }
                            }
                        }

                        // second click move
                        if(event.mouseButton.button == sf::Mouse::Left && press_count == 2){
                            utils.change_turn();
                            move.end = move_from_click(board, mouse_position);
                            piece_moved = chess_pieces.move_piece(window, board, pieces, move);

                            if(piece_moved){ players_turn ^= 1;} // change players
                            press_count = 0;
                        }

                        // right click, may not be used, but make sure to reset count
                        if( event.mouseButton.button == sf::Mouse::Right){ 
                            press_count = 0;
                            puts("r_clear");
                        }
                    }
                    else{
                        // handles any other mouse button events 
                        break;
                    }
                    // default break
                    break;

                }

                // Text entered
                case sf::Event::TextEntered :{

                    // Unicode 13 represents Enter
                    if (event.text.unicode == 13){
                        utils.change_turn();
                        // If user input is valid, then allow move piece
                        if(utils.user_input_valid(user_input)){
                            move = utils.convert_user_input(user_input);
                            piece_moved = chess_pieces.move_piece(window, board, pieces, move);
                        } else { piece_moved = false; }

                        if(piece_moved){ players_turn ^= 1; }
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
        draw_clock_white(window); draw_clock_black(window);
        draw_textbox(window, user_input);
        window.display();
    }

    white_clock_thread.join();
    black_clock_thread.join();
    exit:
    white_clock_thread.detach();
    black_clock_thread.detach();
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