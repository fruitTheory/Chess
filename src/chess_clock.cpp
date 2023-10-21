#include "chess_clock.hpp"
#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>

std::atomic<int> time_left(60);

void start_internal_clock(){
    while(time_left > 0){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        --time_left;
        //std::cout << "Time left: " << time_left << std::endl;
    }
}

void update_clock_display(sf::RenderWindow& window){
    sf::Font font;
    font.loadFromFile("./font/DejaVuSans.ttf");
    sf::Text clock_text;
    clock_text.setFont(font);
    clock_text.setStyle(sf::Text::Bold);
    clock_text.setCharacterSize(20);
    clock_text.setFillColor(sf::Color{185,195,205,255});

    clock_text.setString("Time: " + std::to_string(time_left.load()));

    clock_text.setPosition(800 , 325);
    window.draw(clock_text);

    clock_text.setPosition(800 , 425);
    window.draw(clock_text);

}