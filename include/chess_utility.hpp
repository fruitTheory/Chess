#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"
#include "chess_pieces.hpp"

extern std::pair<Letters, int> notation_map[8][8];
sf::Vector2i mouse_click_position(sf::RenderWindow& window);
void reset_board(sf::RenderWindow& window, Chessboard& board, std::vector<ChessPieces>& chess_pieces);
void initialize_render(sf::RenderWindow& window, Chessboard& board, ChessPieces& chess_pieces, std::vector<ChessPieces> pieces);