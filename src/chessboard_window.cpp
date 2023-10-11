#include "chessboard_window.hpp"

int window_width = 768;
int window_height = 768;

ChessboardWindow::ChessboardWindow():
window_title("Chessboard"),
window_parameters(window_width, window_height),
default_style(sf::Style::Default)
{
    settings.antialiasingLevel = 8;
    window.create(window_parameters, window_title, default_style, settings);
}

sf::RenderWindow& ChessboardWindow::getWindow() { return window; }