#pragma once

// piece id of end sqaure - when using main object
#define PIECE_END_ID piece_map[move.end.number][move.end.letter]

// piece id of end sqaure - when using referenced parameter
#define PIECE_END_ID_REF piece_map[move_end.number][move_end.letter]

// Output stream starting move 
#define debug_MOVE_START std::cout << "Move start: " << move_start.letter << move_start.number << std::endl

// Output stream ending move 
#define debug_MOVE_END std::cout << "Move end: " << move_end.letter << move_end.number << std::endl

/* Default piece IDs */

#define PAWN_WHITE_1   1
#define PAWN_WHITE_2   2
#define PAWN_WHITE_3   3
#define PAWN_WHITE_4   4
#define PAWN_WHITE_5   5
#define PAWN_WHITE_6   6
#define PAWN_WHITE_7   7
#define PAWN_WHITE_8   8

#define BISHOP_WHITE_1 9
#define BISHOP_WHITE_2 10

#define KNIGHT_WHITE_1 11
#define KNIGHT_WHITE_2 12

#define ROOK_WHITE_1   13
#define ROOK_WHITE_2   14

#define QUEEN_WHITE    15
#define KING_WHITE     16

#define PAWN_BLACK_1   17
#define PAWN_BLACK_2   18
#define PAWN_BLACK_3   19
#define PAWN_BLACK_4   20
#define PAWN_BLACK_5   21
#define PAWN_BLACK_6   22
#define PAWN_BLACK_7   23
#define PAWN_BLACK_8   24

#define BISHOP_BLACK_1 25
#define BISHOP_BLACK_2 26

#define KNIGHT_BLACK_1 27
#define KNIGHT_BLACK_2 28

#define ROOK_BLACK_1   29
#define ROOK_BLACK_2   30

#define QUEEN_BLACK    31
#define KING_BLACK     32
