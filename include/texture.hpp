#pragma once

#include "SFML/Graphics.hpp"

class ChessTexture{

    private:

        ChessTexture(){
            bool fReturn = texture.loadFromFile("./img/white_queen.png");
            if( !fReturn ){ puts("Couldn't load .png"); }
        }

        sf::Texture texture;

    public:

        // Returns single instance of texture thanks to static
        static sf::Texture& default_texture(){
            static ChessTexture instance;
            return instance.texture;
        }
        
};