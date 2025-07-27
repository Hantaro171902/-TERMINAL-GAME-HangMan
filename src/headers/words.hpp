#pragma once

#include <string>
#include <vector>

using namespace std;

enum WordTheme { t_animals = 0, t_countries, t_fruits, t_periodic, t_states };

string get_random_word(int min_len, int max_lenmm WordTheme theme);
void load_word_data();

