#pragma once

#include "SFML/Graphics.hpp"

class chessFont{

    public:
        static sf::Font& default_font(){

            static chessFont instance;
            return instance.font;

        }

    private:

        chessFont(){
            if (!font.loadFromFile("./font/DejaVuSans.ttf")){puts("Didnt load .ttf");}
        }

        sf::Font font;
        
};