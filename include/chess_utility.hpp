#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"
#include "chess_pieces.hpp"

extern std::pair<Letters, int> notation_map[8][8];
sf::Vector2i mouse_click_position(ChessboardWindow& window);
void reset_board(ChessboardWindow& window, Chessboard& board, std::vector<ChessPieces>& chess_pieces);
void initialize_display(ChessboardWindow& window, Chessboard& board, ChessPieces& chess_pieces, std::vector<ChessPieces> pieces);