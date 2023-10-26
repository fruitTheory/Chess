#include "chess_utility.hpp"
#include <iostream>

// vector of 2D array
std::vector<std::array<std::array<int, 8>, 8>> game_history;
std::vector<ChessPieces::Move> stored_moves;

// Returns mouse position within bounds of window, else returns -1
sf::Vector2i mouse_click_position(sf::RenderWindow& window){

    extern int window_width; extern int window_height;

    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    if(localPosition.x >= 0 && localPosition.x <= window_width && 
        localPosition.y >= 0 && localPosition.y <= window_height){
            return localPosition;
    }
    sf::Vector2i fail = {-1, -1};
    return fail; // out of bounds
}

void reset_board(sf::RenderWindow& window, Chessboard& board, std::vector<ChessPieces>& pieces){
    ChessPieces chess_pieces;
    extern int piece_map[8][8];
    int reset_map[8][8] = 
    {
    {29, 27, 25, 31, 32, 26, 28, 30},
    {17, 18, 19, 20, 21, 22, 23, 24},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {1,  2,  3,  4,  5,  6,  7,  8},
    {13, 11, 9, 15, 16, 10, 12, 14}
    };
    memcpy(piece_map, reset_map, sizeof(reset_map));
    chess_pieces.update_pieces(window, board, pieces);
}

void store_board_state(){
    extern int piece_map[8][8];
    std::array<std::array<int, 8>, 8> create_page = {0};
    game_history.push_back(create_page); // create a page
    int game_page = game_history.size() - 1; // how many pages -1 for array 
    std::cout << game_page << " game page " << std::endl;
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            game_history[game_page][y][x] = piece_map[y][x];
        }
    }
}

void print_piece_map(){
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            std::cout << piece_map[y][x] << " ";
        }
        puts("");
    }
}

int num = 0;
void print_game_history(){
    
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            std::cout << game_history[num][y][x] << " ";
        }
        puts("");
    }
    num++;
}

void print_stored_moves(){ 
    for(int x = 0; x < 3; x++)
        std::cout << stored_moves[x].start.letter << " " << stored_moves[x].start.number << " ";
    puts("");
}

// temp sprite setup, simple processing 
sf::Sprite setup_sprite(sf::RenderWindow& window){
        
    sf::Vector2f halve(0.5f, 0.5f);
    sf::Color bg(185,195,205,255);

    sf::Texture texture;
    if(!texture.loadFromFile("./img/white_queen.png")) { puts("Error"); }
    sf::Sprite sprite(texture);

    sprite.setTexture(texture);
    sprite.setPosition(50, 50);
    sf::Vector2u originalSize = sprite.getTexture()->getSize();

    float scaleX = 48.0f / originalSize.x;
    float scaleY = 48.0f / originalSize.y;
    sprite.setScale(scaleX, scaleY);

    //window.clear(bg);
    //window.draw(sprite);
    //window.display();

    return sprite;
}