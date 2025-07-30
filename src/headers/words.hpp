// words.hpp
#pragma once

#include <string>
#include <vector>


enum class WordTheme {
    t_animals,
    t_countries,
    t_fruits,
    t_periodic,
    t_states
};

std::string get_random_word(int min_len, int max_len, WordTheme theme);
void load_word_data();

extern std::vector<std::string> words_animals;
extern std::vector<std::string> words_countries;
extern std::vector<std::string> words_fruits;
extern std::vector<std::string> words_periodic;
extern std::vector<std::string> words_states;