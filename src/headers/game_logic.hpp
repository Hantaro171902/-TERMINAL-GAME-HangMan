// game_logic.hpp
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "words.hpp"

enum class GameState { 
    s_playing, 
    s_won, 
    s_lost, 
    s_ended 
};

enum class GuessResult {
    t_waiting, 
    t_correct, 
    t_incorrect, 
    t_duplicate 
};

void start_game(int min_letters, int max_letters, int given, WordTheme theme);
void guess_char(char key);
// void pick_given_letters(int given);
int guesses_incorrect();
int guesses_correct();
void print_level();
void refresh_status();
void refresh_turn();
void print_level();

