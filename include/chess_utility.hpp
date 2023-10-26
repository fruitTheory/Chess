#include "SFML/Graphics.hpp"
#include "chess_pieces.hpp"
#include <array>
#include <vector>

extern std::vector<std::array<std::array<int, 8>, 8>> game_history;
extern std::vector<ChessPieces::Move> stored_moves;
sf::Vector2i mouse_click_position(sf::RenderWindow& window);
void reset_board(sf::RenderWindow& window, Chessboard& board, std::vector<ChessPieces>& pieces);
void store_board_state();
void print_piece_map();
void print_game_history();
void print_stored_moves();