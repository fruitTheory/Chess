#include "chess_window.hpp"


ChessboardWindow::ChessboardWindow():
// retarded syntax, floating scopes, random initializer list, no errors produced if not done correct
window_title("Chessboard"),
window_parameters(768, 768),
default_style(sf::Style::Default)
{
    settings.antialiasingLevel = 8;
    window.create(window_parameters, window_title, default_style, settings);
}

sf::RenderWindow& ChessboardWindow::getWindow() { return window; }