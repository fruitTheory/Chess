#include "chess_clock.hpp"
#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>

std::atomic<int> timeLeft(10);

void countdown(){
    while(timeLeft > 0){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        --timeLeft;
        std::cout << "Time left: " << timeLeft << std::endl;
    }
}

void updateCountdownText(ChessboardWindow& window){
    sf::Font font;
    font.loadFromFile("./font/DejaVuSans.ttf");
    sf::Text countdownText;
    countdownText.setFont(font);
    countdownText.setStyle(sf::Text::Bold);
    countdownText.setCharacterSize(24);
    countdownText.setFillColor(sf::Color{185,195,205,255});

    //countdownText.setString("Time: " + std::to_string(timeLeft.load()));
    countdownText.setString("5:00");

    countdownText.setPosition(800 , 325);
    window.getWindow().draw(countdownText);


    countdownText.setPosition(800 , 425);
    window.getWindow().draw(countdownText);
}