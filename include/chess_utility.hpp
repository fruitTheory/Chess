#include "SFML/Graphics.hpp"
#include "chessboard_window.hpp"


enum Letters { a = 1, b, c, d, e, f, g, h };
extern std::pair<Letters, int> notation_map[8][8];
extern std::map<char, Letters> letter_notation_map;
sf::Vector2i mouse_click_position(ChessboardWindow& window);