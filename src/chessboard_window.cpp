#include "chessboard_window.hpp"
#include "chess_clock.hpp"
#include "chess_text.hpp"

int window_width = 900;
int window_height = 800;

void initialize_window(sf::RenderWindow& window){

    const std::string window_title = "Chessboard";
    const sf::VideoMode window_parameters(window_width, window_height);
    const int default_style = sf::Style::Close; 
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window.create(window_parameters, window_title, default_style, settings);

}

// Updates render for board, pieces, and clock 
void initialize_render(sf::RenderWindow& window, Chessboard& board, ChessPieces& chess_pieces, std::vector<ChessPieces> pieces){
    window.clear();
    chess_pieces.update_pieces(window, board, pieces);
    draw_clock_display(window);
    create_textbox(window);
    window.display(); // initial display
}