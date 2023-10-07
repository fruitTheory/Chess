#include "config.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"




int main(){

    std::cout << "Hello World!\n";

    std::string window_title = "Chessboard";
    sf::VideoMode window_param(768, 768);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    int default_style = sf::Style::Default;

    sf::RenderWindow window(window_param, window_title, default_style, settings);

    sf::Event event;
    sf::Color base_color = {185,195,205,255};
    sf::Color square_color = {0,45,85,255};
    window.clear(base_color); // initial color

    sf::Vector2f board_square_size = {96.f, 96.f};
    sf::RectangleShape board_square(board_square_size);
    board_square.setFillColor(square_color);
    
    // set board up
    int flop = 0;
    for(int y = 0; y < 8; y++){
        int current_y = y * 96;
        for(int i = 0; i < 5; i++){
            window.draw(board_square);
            if(!flop)
                board_square.setPosition((192 * i), current_y);
            if(flop)
                board_square.setPosition((192 * i) + 96, current_y);
            //std::cout << flop << std::endl;
        }
        flop ^= 1;
        //std::cout << "here " << flop << std::endl;
    }

    // initialize pieces
    sf::CircleShape pawn(48.f, 3); // triangle
    sf::CircleShape rook(48.f, 4); //rook.rotate(90); // square
    
    sf::CircleShape king(48.f, 8); // octagon
    sf::CircleShape queen(48.f, 100); // circle
    //queen.setPointCount

    int valid_board[8][8] = {0};

    // set piece original positions
    for(int i = 0; i < 8; i++){
            pawn.setPosition(96 * i, (96 * 6) + 8);
            window.draw(pawn);
    }

    for(int i = 0; i < 2; i++){
            pawn.setPosition(96 * (i * 6), (96 * 7) + 8);
            window.draw(rook);
    }

    // Main window
    while (window.isOpen()){
        // check events that were triggered since the last iteration
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed){ window.close(); }


        
        window.display();
    }

    return EXIT_SUCCESS;
}