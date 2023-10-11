#include "chess_utility.hpp"

// Returns mouse position within bounds of window, else returns -1
sf::Vector2i mouse_click_position(ChessboardWindow& window){

        extern int window_width; extern int window_height;

        sf::Vector2i localPosition = sf::Mouse::getPosition(window.getWindow());
        if(localPosition.x >= 0 && localPosition.x <= window_width && 
           localPosition.y >= 0 && localPosition.y <= window_height){
                return localPosition;
        }
        sf::Vector2i fail = {-1, -1};
        return fail; // out of bounds
}
