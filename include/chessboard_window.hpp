#pragma once

#include "SFML/Graphics.hpp"

class ChessboardWindow{
private:
    const std::string window_title;
    const sf::VideoMode window_parameters;
    const int default_style; 
    sf::RenderWindow window;
    sf::ContextSettings settings;

public:
    ChessboardWindow();
    sf::RenderWindow& getWindow();
};
