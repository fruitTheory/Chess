#include "chess_utility.hpp"
#include "chess_pieces.hpp"

// General Notation mapping
// std::pair<Letters, int> notation_map[8][8] = {
//     {{a, 8}, {b, 8}, {c, 8}, {d, 8}, {e, 8}, {f, 8}, {g, 8}, {h, 8}},
//     {{a, 7}, {b, 7}, {c, 7}, {d, 7}, {e, 7}, {f, 7}, {g, 7}, {h, 7}},
//     {{a, 6}, {b, 6}, {c, 6}, {d, 6}, {e, 6}, {f, 6}, {g, 6}, {h, 6}},
//     {{a, 5}, {b, 5}, {c, 5}, {d, 5}, {e, 5}, {f, 5}, {g, 5}, {h, 5}},
//     {{a, 4}, {b, 4}, {c, 4}, {d, 4}, {e, 4}, {f, 4}, {g, 4}, {h, 4}},
//     {{a, 3}, {b, 3}, {c, 3}, {d, 3}, {e, 3}, {f, 3}, {g, 3}, {h, 3}},
//     {{a, 2}, {b, 2}, {c, 2}, {d, 2}, {e, 2}, {f, 2}, {g, 2}, {h, 2}},
//     {{a, 1}, {b, 1}, {c, 1}, {d, 1}, {e, 1}, {f, 1}, {g, 1}, {h, 1}},
// };

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

// temp sprite setup, simple processing 
sf::Sprite setup_sprite(ChessboardWindow& window){
        
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

        window.getWindow().clear(bg);
        window.getWindow().draw(sprite);
        window.getWindow().display();

        return sprite;
}

void reset_board(ChessboardWindow& window, Chessboard& board, std::vector<ChessPieces>& chess_pieces){
        ChessPieces pieces;
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
       pieces.setup_pieces(window, board, chess_pieces);
}