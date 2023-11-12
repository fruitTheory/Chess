#include "chess_utility.hpp"
#include "chess_history.hpp"
#include <iostream>

int players_turn = PLAYER::WHITE; // global player turn white:1 black:0

// A check for whos turn it is, will set the correct players turn globally
void ChessUtility::change_turn(){
    players_turn == 1 ? players_turn = PLAYER::WHITE : players_turn = PLAYER::BLACK;
}

// General notation map
const std::pair<Letters, int> notation_map[8][8] = {
    {{Letters::a, 8}, {Letters::b, 8}, {Letters::c, 8}, {Letters::d, 8}, {Letters::e, 8}, {Letters::f, 8}, {Letters::g, 8}, {Letters::h, 8}},
    {{Letters::a, 7}, {Letters::b, 7}, {Letters::c, 7}, {Letters::d, 7}, {Letters::e, 7}, {Letters::f, 7}, {Letters::g, 7}, {Letters::h, 7}},
    {{Letters::a, 6}, {Letters::b, 6}, {Letters::c, 6}, {Letters::d, 6}, {Letters::e, 6}, {Letters::f, 6}, {Letters::g, 6}, {Letters::h, 6}},
    {{Letters::a, 5}, {Letters::b, 5}, {Letters::c, 5}, {Letters::d, 5}, {Letters::e, 5}, {Letters::f, 5}, {Letters::g, 5}, {Letters::h, 5}},
    {{Letters::a, 4}, {Letters::b, 4}, {Letters::c, 4}, {Letters::d, 4}, {Letters::e, 4}, {Letters::f, 4}, {Letters::g, 4}, {Letters::h, 4}},
    {{Letters::a, 3}, {Letters::b, 3}, {Letters::c, 3}, {Letters::d, 3}, {Letters::e, 3}, {Letters::f, 3}, {Letters::g, 3}, {Letters::h, 3}},
    {{Letters::a, 2}, {Letters::b, 2}, {Letters::c, 2}, {Letters::d, 2}, {Letters::e, 2}, {Letters::f, 2}, {Letters::g, 2}, {Letters::h, 2}},
    {{Letters::a, 1}, {Letters::b, 1}, {Letters::c, 1}, {Letters::d, 1}, {Letters::e, 1}, {Letters::f, 1}, {Letters::g, 1}, {Letters::h, 1}}
};

// Convert user input to move type
ChessPieces::Move ChessUtility::convert_user_input( std::string user_input ) {

    // temp user note for function, need to check letter input for actual letter
    ChessPieces::Move move;
    ChessPieces::Move_data move_data;

    // Convert data for move start
    try{
    move_data.letter = static_cast<int>(letter_notation_map.at(user_input[0]));
    } catch(const std::out_of_range& err){ puts("Out of Range caught: start letter");}
    move_data.number = user_input[1] - '0';
    move.start = move_data;

    // Convert data for move end
    try{
    move_data.letter = static_cast<int>(letter_notation_map.at(user_input[3]));
    }catch(const std::out_of_range& err){ puts("Out of Range caught: end letter");}
    move_data.number = user_input[4] - '0';
    move.end = move_data;

    return move;

}

// Check if user text input is valid
bool ChessUtility::user_input_valid( std::string user_input ) {

    // Special cases - castling
    if(user_input.length() == 3 && user_input == "0-0"){ puts("castle short"); return true; }
    if(user_input.length() == 5 && user_input == "0-0-0"){ puts("castle long"); return true; }

    // legal move range
    if(user_input.length() == 5){ 
        // invalid if move number is out of range
        if(user_input[1] - '0' > 8 || user_input[1] - '0' < 1){ 
            puts("Not a valid move input");
            return false;
        }
        // invalid if move number is out of range
        else if(user_input[4] - '0' > 8 || user_input[4] - '0' < 1) {
            puts("Not a valid move input");
            return false;
        }
        else{
            return true; 
        }
    }
    // invalid move lengths
    if(user_input.length() > 5 || user_input.length() < 5){
        puts("Not a valid move input - Select a piece and destination - Ex: c1 f4, c2 c4");
        return false;
    }
    
    // any other situations
    puts("Not a valid piece");
    return false;
}

void ChessUtility::print_piece_map(){
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            std::cout << piece_map[y][x] << " ";
        }
        puts("");
    }
}

// int game_page = 0; // replace this
void ChessUtility::print_game_history(){

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            std::cout << game_history[game_page][y][x] << " ";
        }
        puts("");
    }
    game_page++;
}

void ChessUtility::print_stored_moves(){ 
    for(int x = 0; x < 3; x++)
        std::cout << stored_moves[x].start.letter << " " << stored_moves[x].start.number << " ";
    puts("");
}

void ChessUtility::print_last_move(){ 
    for(int x = 0; x < 2; x++)
        std::cout << stored_moves[x].start.letter << stored_moves[x].start.number << " ";
    puts("");
}