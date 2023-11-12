#include "chess_clock.hpp"
#include "font.hpp"
#include "chess_utility.hpp"
#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>

int start_min = 5;
int start_sec = 0;
int w_minutes = start_min;
int w_seconds = start_sec;
int b_minutes = start_min;
int b_seconds = start_sec;
int time_left_white(60*w_minutes);
int time_left_black(60*b_minutes);

// start after first player makes move
void start_clock_white(){
   
    while(time_left_white > 0){

        if(players_turn == PLAYER::WHITE){
            
            if(time_left_white  % 60 == 0){ w_minutes -= 1; }
            w_seconds -= 1;
            if(w_seconds < 0){ w_seconds = 59; }

            std::this_thread::sleep_for(std::chrono::seconds(1));
            --time_left_white;
            if(time_left_white == 0){ break; }
        }
    }
}

void start_clock_black(){

    while(time_left_black > 0){

        if(players_turn == PLAYER::BLACK){

            if(time_left_black  % 60 == 0){ b_minutes -= 1; }
            b_seconds -= 1;
            if(b_seconds < 0){ b_seconds = 59; }

            std::this_thread::sleep_for(std::chrono::seconds(1));
            --time_left_black;
            if(time_left_black == 0){ break; }
        }
    }
}

void draw_clock_white(sf::RenderWindow& window){

    sf::Font& font = ChessFont::default_font();
    sf::Text clock_text;
    
    clock_text.setFont(font);
    clock_text.setStyle(sf::Text::Bold);
    clock_text.setCharacterSize(20);
    clock_text.setFillColor(sf::Color{185,195,205,255});

    if(w_seconds < 10){ clock_text.setString("Time: " + std::to_string(w_minutes) + ":" + "0" + std::to_string(w_seconds)); }
    else { clock_text.setString("Time: " + std::to_string(w_minutes) + ":" + std::to_string(w_seconds)); }

    clock_text.setPosition(780 , 425);
    window.draw(clock_text);

}

void draw_clock_black(sf::RenderWindow& window){

    sf::Font& font = ChessFont::default_font();
    sf::Text clock_text;
    
    clock_text.setFont(font);
    clock_text.setStyle(sf::Text::Bold);
    clock_text.setCharacterSize(20);
    clock_text.setFillColor(sf::Color{185,195,205,255});

    if(b_seconds < 10){ clock_text.setString("Time: " + std::to_string(b_minutes) + ":" + "0" + std::to_string(b_seconds)); }
    else { clock_text.setString("Time: " + std::to_string(b_minutes) + ":" + std::to_string(b_seconds)); }

    clock_text.setPosition(780 , 325);
    window.draw(clock_text);

}