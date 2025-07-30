// main.cpp

#include <iostream>
#include "menu.hpp"
#include "cursor_input.hpp"
#include "ultils.hpp"
#include "words.hpp"

using namespace std;

int main(){
    // load_word_data();
    // cout << "Words loaded: " << words_animals.size() << " animals, "
    //     << words_countries.size() << " countries, "
    //     << words_fruits.size() << " fruits, "
    //     << words_periodic.size() << " periodic, "
    //     << words_states.size() << " states." << endl;


	//Setup console
	toggle_cursor(false);
	// console_size(800,600);

	//Loop game forever
	while(true){
		menu();
    }

	return 0;
}