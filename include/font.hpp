#pragma once

#include "SFML/Graphics.hpp"

class ChessFont{

    private:

        ChessFont(){
            bool fReturn = font.loadFromFile("./font/DejaVuSans.ttf");
            if( !fReturn ){ puts("Didn't load .ttf"); }
        }

        sf::Font font;

    public:

        // Returns single instance of font thanks to static
        static sf::Font& default_font(){
            static ChessFont instance;
            return instance.font;
        }
        
};