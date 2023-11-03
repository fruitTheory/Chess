#include "chess_history.hpp"
#include <iostream>


// vector of 2D arrays
std::vector<std::array<std::array<int, 8>, 8>> game_history;
// stored moves that were converted to relevant array position
std::vector<ChessPieces::Move> stored_moves;


void store_board_state(){
    extern int piece_map[8][8];
    std::array<std::array<int, 8>, 8> create_page = {0};
    game_history.push_back(create_page); // create a page
    int game_page = game_history.size() - 1; // how many pages -1 for array 
    // std::cout << "game page: " << game_page <<  std::endl;
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            game_history[game_page][y][x] = piece_map[y][x];
        }
    }
}