#pragma once

// piece id of end sqaure - when using main object
#define PIECE_END_ID piece_map[move.end.number][move.end.letter]

// piece id of end sqaure - when using referenced parameter
#define PIECE_END_ID_REF piece_map[move_end.number][move_end.letter]

// Output stream starting move 
#define debug_MOVE_START std::cout << "Move start: " << move_start.letter << move_start.number << std::endl

// Output stream ending move 
#define debug_MOVE_END std::cout << "Move end: " << move_end.letter << move_end.number << std::endl
