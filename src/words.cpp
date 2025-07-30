// words.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <ctime>
#include "words.hpp"

using namespace std;

// const int count_animals = 214;
// const int count_countries = 174;
// const int count_fruits = 73;
// const int count_periodic = 118;
// const int count_states = 39;

// Word lists for each theme
vector<string> words_animals;
vector<string> words_countries;
vector<string> words_fruits;
vector<string> words_periodic;
vector<string> words_states;

static void load_words_from_file(const string& filename, vector<string>& container) {
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty())
            container.push_back(line);
    }
}

void load_word_data() {
    load_words_from_file("./assets/animals.txt", words_animals);
    load_words_from_file("./assets/countries.txt", words_countries);
    load_words_from_file("./assets/fruits.txt", words_fruits);
    load_words_from_file("./assets/periodic.txt", words_periodic);
    load_words_from_file("./assets/states.txt", words_states);
}

string get_random_word(int min_len, int max_len, WordTheme theme) {
    vector<string>* word_list = nullptr;

    switch (theme) {
        case WordTheme::t_animals:   word_list = &words_animals; break;
        case WordTheme::t_countries: word_list = &words_countries; break;
        case WordTheme::t_fruits:    word_list = &words_fruits; break;
        case WordTheme::t_periodic:  word_list = &words_periodic; break;
        case WordTheme::t_states:    word_list = &words_states; break;
        default: return "error";
    }

    if (!word_list || word_list->empty()) return "";

    vector<string> filtered;
    for (const auto& word : *word_list) {
        if (word.length() >= min_len && word.length() <= max_len)
            filtered.push_back(word);
    }

    if (filtered.empty()) return "error";

    srand(time(NULL));
    int index = rand() % filtered.size();
    return filtered[index];
}