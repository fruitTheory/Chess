#include "chess_clock.hpp"
#include "font.hpp"
#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>

int minutes = 5;
int seconds = 59;
// not necessary to be atomic but good practice
std::atomic<int> time_left(60*minutes);

// start after first player makes move
void start_internal_clock(){

    while(time_left > 0){

        if(time_left.load()  % 60 == 0){ minutes -= 1; }

        std::this_thread::sleep_for(std::chrono::seconds(1));

        --time_left;

        if(time_left == 0){ break; }

        seconds -= 1;
        if(seconds < 0){ seconds = 59; }
    }
}

void draw_clock_display(sf::RenderWindow& window){

    sf::Font& font = ChessFont::default_font();
    sf::Text clock_text;
    
    clock_text.setFont(font);
    clock_text.setStyle(sf::Text::Bold);
    clock_text.setCharacterSize(20);
    clock_text.setFillColor(sf::Color{185,195,205,255});

    if(seconds < 10){ clock_text.setString("Time: " + std::to_string(minutes) + ":" + "0" + std::to_string(seconds)); }
    else { clock_text.setString("Time: " + std::to_string(minutes) + ":" + std::to_string(seconds)); }

    clock_text.setPosition(780 , 325);
    window.draw(clock_text);

    clock_text.setPosition(780 , 425);
    window.draw(clock_text);

}