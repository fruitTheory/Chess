#include "chess_mouse.hpp"
#include "chess_utility.hpp"

// Returns mouse position within bounds of window, else returns -1
sf::Vector2i get_mouse_position(sf::RenderWindow& window){

    extern int window_width, window_height;

    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    if(localPosition.x >= 0 && localPosition.x <= window_width && 
        localPosition.y >= 0 && localPosition.y <= window_height){
            return localPosition;
    }
    sf::Vector2i fail = {-1, -1};
    return fail; // out of bounds
}

ChessPieces::Move_data move_from_click(Chessboard& board, sf::Vector2i mouse_position){

    ChessPieces::Move_data m_data;

    // Size is 96 by default, the division or position converts to array number
    int square_size = board.get_square_size();
    int arr_x = mouse_position.x / square_size;
    int arr_y = mouse_position.y / square_size;

    m_data.letter = (int)notation_map[arr_y][arr_x].first;
    m_data.number = notation_map[arr_y][arr_x].second;

    return m_data;

}