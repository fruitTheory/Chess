#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class ChessFont{

    public:

        // Returns single instance of font thanks to static
        static sf::Font& default_font(){
            static ChessFont instance;
            return instance.font;
        }

    private:

        ChessFont(){
            bool fReturn = font.loadFromFile("./font/DejaVuSans.ttf");
            if( !fReturn ){ std::cerr << "Didn't load .ttf" << std::endl; }
        }

        sf::Font font;
        
};