#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"
#include "chess_pieces.hpp"


extern std::pair<Letters, int> notation_map[8][8];
sf::Vector2i mouse_click_position(ChessboardWindow& window);