// game_logic.cpp
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>	// for tolower, isalpha
#include <set>

#include "game_logic.hpp"
#include "ultils.hpp"
#include "words.hpp"

using namespace std;

string word;
string guess;
string incorrect = "______";
set<char> guess_letters; 	// Store all guess letters (right && wrong)

GameState status;
GuessResult turn;
WordTheme theme;
int min_letters;
int max_letters;

void start_game(int min_letters_, int max_letters_, int given, WordTheme theme_){
	//Reset incorrect guesses
	incorrect = "______";

	//Setup Game 
	status = GameState::s_playing;
	theme = theme_;
	turn = GuessResult::t_waiting;
	min_letters = min_letters_;
	max_letters = max_letters_;

	// Load data
	load_word_data();
		
	word = get_random_word(min_letters, max_letters, theme);
	if (word.empty()) {
        cout << "No words available for this theme and length. Returning to menu." << endl;
        status = GameState::s_ended;
        return;
    }
	guess = string(word.length(), '_');
	// pick_given_letters(given);

	// load_word_data(min_letters,max_letters,theme);
	// pick_given_letters(given);

	//Game Loop
	while(status == GameState::s_playing){
		print_level();
		refresh_turn();
		refresh_status();
	}
	
	//Print end screens
	print_level();
	getch();
	status = GameState::s_ended;

	// //Release memory - This causes crashing for some reason
	// delete word;
	// delete guess;
}

// void load_word_data(){
// 	//Get size of the word array
// 	int theme = 0;
// 	WordTheme selected_theme = static_cast<WordTheme>(theme);
// 	int size = 0;

// 	if (theme == t_animals){
// 		size = count_animals;
// 	}else if (theme == t_countries){
// 		size = count_countries;
// 	}else if (theme == t_fruits){
// 		size = count_fruits;
// 	}else if (theme == t_periodic){
// 		size = count_periodic;
// 	}else if (theme == t_states){
// 		size = count_states;
// 	}

// 	//Get the word associated with the random index and copy it into word and guess vars
// 	SYSTEMTIME time;
// 	int random_index;
// 	bool found = false;
// 	while (!found){

// 		//Get random index for words
// 		GetSystemTime(&time);
// 		srand((unsigned)time.wMilliseconds);
// 		random_index = rand() % size;

// 		int length = 0;
// 		if (theme == t_animals){
// 			length = strlen(words_animals[random_index]);
// 		}else if (theme == t_countries){
// 			length = strlen(words_countries[random_index]);
// 		}else if (theme == t_fruits){
// 			length = strlen(words_fruits[random_index]);
// 		}else if (theme == t_periodic){
// 			length = strlen(words_periodic[random_index]);
// 		}else if (theme == t_states){
// 			length = strlen(words_states[random_index]);
// 		}

// 		//Check if length
// 		if (length >= min_letters && length <= max_letters){
// 			found = true;
// 		}
// 	}

// 	//Get word
// 	if (theme == t_animals){
// 		word = new char[1+strlen(words_animals[random_index])];
// 		strcpy(word,words_animals[random_index]);
// 	}else if (theme == t_countries){
// 		word = new char[1+strlen(words_countries[random_index])];
// 		strcpy(word,words_countries[random_index]);
// 	}else if (theme == t_fruits){
// 		word = new char[1+strlen(words_fruits[random_index])];
// 		strcpy(word,words_fruits[random_index]);
// 	}else if (theme == t_periodic){
// 		word = new char[1+strlen(words_periodic[random_index])];
// 		strcpy(word,words_periodic[random_index]);
// 	}else if (theme == t_states){
// 		word = new char[1+strlen(words_states[random_index])];
// 		strcpy(word,words_states[random_index]);
// 	}

// 	//Fill in guess with spaces
// 	guess = new char[1+strlen(word)];
// 	strcpy(guess,word);
// 	for (int i=0; i<strlen(guess); i++){
// 		guess[i] = '_';
// 	}
// }

// void pick_given_letters(int given){
// 	//Loop given amount of times
// 	int picked = 0;
// 	srand(time(NULL));
// 	while (picked != given) {
// 		sleep_ms(10);
// 		int index = rand() % guess.length();
// 		if (guess[index] == '_') {
// 			guess_char(word[index]);
// 			picked++;
// 		}
// 	}
// }

void print_level(){
	clearScreen();

	//Print header
	cout << "-----------------------------Press Escape to quit-------------------------------"<<endl;
	cout << "        _   _                  ___  ___            " << endl;
	cout << "       | | | |                 |  \\/  |            " << endl;
	cout << "       | |_| | __ _ _ __   __ _| .  . | __ _ _ __  " << endl;
	cout << "       |  _  |/ _` | '_ \\ / _` | |\\/| |/ _` | '_ \\ " << endl;
	cout << "       | | | | (_| | | | | (_| | |  | | (_| | | | |" << endl;
	cout << "       \\_| |_/\\__,_|_| |_|\\__, \\_|  |_/\\__,_|_| |_|" << endl;
	cout << "                           __/ |                   " << endl;
	cout << "                          |___/                    " << endl;
	
	//Print status
	if (status == GameState::s_playing){
		cout << endl << "--------------------Please guess by pressing any letter-------------------------"<<endl<<endl;
	}else if (status == GameState::s_won){
		cout << endl << "------------------Please press any key to return to menu------------------------"<<endl<<endl;
	}else if (status = GameState::s_lost){
		cout << endl << "------------------Please press any key to return to menu------------------------"<<endl<<endl;
	}else{
		cout << endl  << "--------------------------------------------------------------------------------"<<endl<<endl;
	}

	if (status == GameState::s_lost){

		//Print currently guessed
		// cout << "  ";
		// for (int i=0; i<strlen(word); i++){
		// 	cout << word[i];
		// }
		// cout << endl << endl;
		cout << " " << word << endl << endl;
	} else {
	
		//Print currently guessed
		cout << "  ";
		// for (int i=0; i<strlen(guess); i++){
		// 	cout << guess[i] << " ";
		// }
		// cout << endl << endl;
		cout << " ";
		for (char c : guess)
			cout << c << " ";
		cout << endl << endl;
	}

	//Print hangman according to state
	int guesses = guesses_incorrect();
	switch (guesses){
		case 0:
			cout << "  +----+"		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |" 			<<endl;
			cout << "  |" 			<<endl;
			cout << "  |" 			<<endl;
			cout << "  |" 			<<endl;
			cout << "  |" 			<<endl;
			cout << "  |" 			<<endl;
			cout << "  +=========" 	<<endl;
		break;
		case 1:
			cout << "  +----+" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |    O" 		<<endl;
			cout << "  |" 			<<endl;
			cout << "  |" 			<<endl;
			cout << "  |" 			<<endl;
			cout << "  |" 			<<endl;
			cout << "  |" 			<<endl;
			cout << "  +=========" 	<<endl;
		break;
		case 2:
			cout << "  +----+" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |    O" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |" 			<<endl;
			cout << "  |" 			<<endl;
			cout << "  |" 			<<endl;
			cout << "  +=========" 	<<endl;
		break;
		case 3:
			cout << "  +----+" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |    O" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |     \\" 	<<endl;
			cout << "  |      \\" 	<<endl;
			cout << "  |" 			<<endl;
			cout << "  +=========" 	<<endl;
		break;
		case 4:
			cout << "  +----+" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |    O" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |   / \\" 	<<endl;
			cout << "  |  /   \\" 	<<endl;
			cout << "  |" 			<<endl;
			cout << "  +=========" 	<<endl;
		break;
		case 5:
			cout << "  +----+" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |    O" 		<<endl;
			cout << "  |   /|" 		<<endl;
			cout << "  |  / |" 		<<endl;
			cout << "  |   / \\" 	<<endl;
			cout << "  |  /   \\" 	<<endl;
			cout << "  |" 			<<endl;
			cout << "  +=========" 	<<endl;
		break;
		default:
			cout << "  +----+" 		<<endl;
			cout << "  |    |" 		<<endl;
			cout << "  |    O" 		<<endl;
			cout << "  |   /|\\" 	<<endl;
			cout << "  |  / | \\" 	<<endl;
			cout << "  |   / \\" 	<<endl;
			cout << "  |  /   \\" 	<<endl;
			cout << "  |" 			<<endl;
			cout << "  +=========" 	<<endl;
		break;
	}
	
	//Show user number of guesses left
	cout << endl << "  ";
	if (guesses == 6){
		cout << "No guesses left" << endl;
	}else if (guesses == 5){
		cout << "1 guess left" << endl;
	}else{
		int left = 6 - guesses;
		cout << left << " guesses left" << endl;
	}
	cout << endl;
	
	//Print currently guessed
	cout << "  ";
	for (char c : incorrect) {
		if (isalpha(c) || c == '_'){
			cout << c << " ";
		}
	}
	cout << endl;
	
	//Footer
	if (status == GameState::s_playing){
		if (turn == GuessResult::t_correct){
			cout << endl << endl << "------------------------Guess was correct, well done----------------------------"<<endl;
		}else if (turn == GuessResult::t_incorrect){
			cout << endl << endl << "----------------------------Guess was incorrect---------------------------------"<<endl;
		}else if (turn == GuessResult::t_duplicate){
			cout << endl << endl << "----------------------This letter has alreay been guessed-----------------------"<<endl;
		}else{
			cout << endl << endl << "--------------------------------------------------------------------------------"<<endl;
		}
	}else if (status == GameState::s_won){
		cout << endl << endl << "-------------------------Whoop you won the game!!-------------------------------"<<endl;
	}else if (status == GameState::s_lost){
		cout << endl << endl << "-------------------------Dammit you lost this one-------------------------------"<<endl;
	}else{
		cout << endl << endl << "--------------------------------------------------------------------------------"<<endl;
	}
}

void refresh_status(){
	if (guesses_correct() == word.length()){
		status = GameState::s_won;
	}else if (guesses_incorrect() == 6){
		status = GameState::s_lost;
	}else{
		status = GameState::s_playing;
	}
}

void refresh_turn(){
	turn = GuessResult::t_waiting;

	//Get key pressed
	char key = getch();

	//Exit game if key is escape
	if (key == 27){
		exit(0);
	}

	//Check key is in the alphabet
	if (!isalpha(key)){
		return;
	}

	guess_char(key);
}

void guess_char(char key){
	bool found = false;

	// for (char c : guess) {
	// 	if (tolower(key) == c){
	// 		turn = GameState::t_duplicate;
	// 		return;
	// 	}
	// }

	for (int i = 0; i < word.length(); i++){
		//Compare guess char with the key pressed
		if (tolower(word[i]) == tolower(key)){
			//Replace guess letter with actual letter if guessed correct
			guess[i] = word[i];
			turn = GuessResult::t_correct;
			found = true;
		}
	}


	if (!found) {
		for (int i = 0; i < incorrect.length(); i++) {
			if (incorrect[i] == '_') {
				incorrect[i] = key;
				turn = GuessResult::t_incorrect;
				return;
			}
		}
	}
}

int guesses_incorrect(){
    int guesses = 0;
    for (char c : incorrect) {
        if (isalpha(c)) {
            guesses++;
        }
    }
    return guesses;
}

int guesses_correct(){
	int guesses = 0;
	for (char c : guess){
		if (c != '_'){
			guesses++;
		}
	}
	return guesses;
}    // Show current level