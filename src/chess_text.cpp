#include "chess_text.hpp"
#include "font.hpp"


void create_textbox(sf::RenderWindow &window){

    sf::Vector2f box_size(88.f, 40.f);
    sf::RectangleShape box(box_size);

    sf::Font &font = chessFont::default_font();

    sf::Text text("", font, 24);
    text.setPosition(800 , 525);
    text.setFillColor(sf::Color::Black);

    box.setSize({88.f, 40.f});
    box.setPosition(800 , 525);
    box.setFillColor(sf::Color::White);

    window.draw(box);
    window.draw(text);

}

// if (event.type == sf::Event::TextEntered){
//     if (event.text.unicode == 8 && text.getString().getSize() > 0){
//         std::string t = text.getString();
//         t.pop_back();
//         text.setString(t);
//     } 
//     else if (event.text.unicode < 128 && event.text.unicode != 8){ // Exclude non-ASCII and backspace
//         text.setString(text.getString() + static_cast<char>(event.text.unicode));
//     }