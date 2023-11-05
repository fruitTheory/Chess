#pragma once

#include "chess_pieces.hpp"
#include <utility>

extern int players_turn;

extern const std::pair<Letters, int> notation_map[8][8];

namespace PLAYER{
    enum ePLAYER { BLACK = 0, WHITE = 1};
}

class ChessUtility{
    private:
        //int game_page;
    public:
        ChessPieces::Move convert_user_input( std::string user_input );
        bool user_input_valid( std::string user_input );

        void print_piece_map();
        void print_game_history();
        void print_stored_moves();
        void print_last_move();
        void check_turn();
};

