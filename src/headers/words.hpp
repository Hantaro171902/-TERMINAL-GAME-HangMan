// words.hpp
#pragma once

#include <string>
#include <vector>

using namespace std;

enum class WordTheme {
    t_animals,
    t_countries,
    t_fruits,
    t_periodic,
    t_states
};

string get_random_word(int min_len, int max_len, WordTheme theme);
void load_word_data();

extern vector<string> words_animals;
extern vector<string> words_countries;
extern vector<string> words_fruits;
extern vector<string> words_periodic;
extern vector<string> words_states;