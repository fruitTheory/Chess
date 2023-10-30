#include "chess_utility.hpp"
#include "chess_history.hpp"
#include <iostream>

void print_piece_map(){
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            std::cout << piece_map[y][x] << " ";
        }
        puts("");
    }
}

int num = 0; // replace this
void print_game_history(){
    
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            std::cout << game_history[num][y][x] << " ";
        }
        puts("");
    }
    num++;
}

void print_stored_moves(){ 
    for(int x = 0; x < 3; x++)
        std::cout << stored_moves[x].start.letter << " " << stored_moves[x].start.number << " ";
    puts("");
}