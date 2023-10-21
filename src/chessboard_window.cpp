#include "chessboard_window.hpp"

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