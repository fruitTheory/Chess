#include "chess_text.hpp"
#include "font.hpp"


void draw_textbox(sf::RenderWindow &window, std::string user_input){

    sf::Vector2f box_size(88.f, 40.f);
    sf::RectangleShape box(box_size);
    sf::Font &font = ChessFont::default_font();
    sf::Text text("Null", font, 24);

    box.setPosition(800 , 525);
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);

    text.setPosition(800 , 525);
    text.setFillColor(sf::Color::Black);
    text.setString(user_input);

    window.draw(box);
    window.draw(text);

}