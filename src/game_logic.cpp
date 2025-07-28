#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "game_logic.hpp"
#include "ultils.hpp"
#include "words.hpp"

using namespace std;

char *word;
char *guess;
char incorrect[7] = {'_'};

int status;
int turn;

void start_game(int min_letters, int max_letters, int given, int theme){
	//Reset incorrect guesses
	strcpy(incorrect,"______");

	//Setup Game 
	status = s_playing;
	load_word_data(min_letters,max_letters,theme);
	pick_given_letters(given);
	turn = t_waiting;

	//Game Loop
	while(status == s_playing){
		print_level();
		refresh_turn();
		refresh_status();
	}
	
	//Print end screens
	print_level();
	_getch();
	status = s_ended;

	//Release memory - This causes crashing for some reason
	delete word;
	delete guess;
}

void load_word_data(int min_letters, int max_letters, int theme){
	//Get size of the word array
	int size = 0;
	if (theme == t_animals){
		size = count_animals;
	}else if (theme == t_countries){
		size = count_countries;
	}else if (theme == t_fruits){
		size = count_fruits;
	}else if (theme == t_periodic){
		size = count_periodic;
	}else if (theme == t_states){
		size = count_states;
	}

	//Get the word associated with the random index and copy it into word and guess vars
	SYSTEMTIME time;
	int random_index;
	bool found = false;
	while (!found){

		//Get random index for words
		GetSystemTime(&time);
		srand((unsigned)time.wMilliseconds);
		random_index = rand() % size;

		int length = 0;
		if (theme == t_animals){
			length = strlen(words_animals[random_index]);
		}else if (theme == t_countries){
			length = strlen(words_countries[random_index]);
		}else if (theme == t_fruits){
			length = strlen(words_fruits[random_index]);
		}else if (theme == t_periodic){
			length = strlen(words_periodic[random_index]);
		}else if (theme == t_states){
			length = strlen(words_states[random_index]);
		}

		//Check if length
		if (length >= min_letters && length <= max_letters){
			found = true;
		}
	}

	//Get word
	if (theme == t_animals){
		word = new char[1+strlen(words_animals[random_index])];
		strcpy(word,words_animals[random_index]);
	}else if (theme == t_countries){
		word = new char[1+strlen(words_countries[random_index])];
		strcpy(word,words_countries[random_index]);
	}else if (theme == t_fruits){
		word = new char[1+strlen(words_fruits[random_index])];
		strcpy(word,words_fruits[random_index]);
	}else if (theme == t_periodic){
		word = new char[1+strlen(words_periodic[random_index])];
		strcpy(word,words_periodic[random_index]);
	}else if (theme == t_states){
		word = new char[1+strlen(words_states[random_index])];
		strcpy(word,words_states[random_index]);
	}

	//Fill in guess with spaces
	guess = new char[1+strlen(word)];
	strcpy(guess,word);
	for (int i=0; i<strlen(guess); i++){
		guess[i] = '_';
	}
}
void pick_given_letters(int given){
	//Loop given amount of times
	SYSTEMTIME time;
	int random_index;
	int picked = 0;
	while (picked != given){

		//Pick random index of string
		Sleep(10);
		GetSystemTime(&time);
		srand((unsigned)time.wMilliseconds);
		random_index = rand() % strlen(guess);

		//Check if letter has been given already
		if (guess[random_index] == '_'){
			
			//Fill in the letter in the guess string
			guess_char(word[random_index]);

			//guess[random_index] = word[random_index];
			picked += 1;
		}
	}
}

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
	if (status == s_playing){
		cout << endl << "--------------------Please guess by pressing any letter-------------------------"<<endl<<endl;
	}else if (status == s_won){
		cout << endl << "------------------Please press any key to return to menu------------------------"<<endl<<endl;
	}else if (status = s_lost){
		cout << endl << "------------------Please press any key to return to menu------------------------"<<endl<<endl;
	}else{
		cout << endl  << "--------------------------------------------------------------------------------"<<endl<<endl;
	}

	if (status == s_lost){

		//Print currently guessed
		cout << "  ";
		for (int i=0; i<strlen(word); i++){
			cout << word[i];
		}
		cout << endl << endl;
	}else{
	
		//Print currently guessed
		cout << "  ";
		for (int i=0; i<strlen(guess); i++){
			cout << guess[i] << " ";
		}
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
	for (int i=0; i<strlen(incorrect); i++){
		if (isalpha(incorrect[i]) || incorrect[i] == '_'){
			cout << incorrect[i] << " ";
		}
	}
	cout << endl;
	
	//Footer
	if (status == s_playing){
		if (turn == t_correct){
			cout << endl << endl << "------------------------Guess was correct, well done----------------------------"<<endl;
		}else if (turn == t_incorrect){
			cout << endl << endl << "----------------------------Guess was incorrect---------------------------------"<<endl;
		}else if (turn == t_duplicate){
			cout << endl << endl << "----------------------This letter has alreay been guessed-----------------------"<<endl;
		}else{
			cout << endl << endl << "--------------------------------------------------------------------------------"<<endl;
		}
	}else if (status == s_won){
		cout << endl << endl << "-------------------------Whoop you won the game!!-------------------------------"<<endl;
	}else if (status = s_lost){
		cout << endl << endl << "-------------------------Dammit you lost this one-------------------------------"<<endl;
	}else{
		cout << endl << endl << "--------------------------------------------------------------------------------"<<endl;
	}
}
void refresh_status(){
	if (guesses_correct() == strlen(word)){
		status = s_won;
	}else if (guesses_incorrect() == 6){
		status = s_lost;
	}else{
		status = s_playing;
	}
}
void refresh_turn(){
	turn = t_waiting;

	//Get key pressed
	char key = _getch();

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
	for (int i=0; i<strlen(guess); i++){
		if (tolower(key) == guess[i]){
			turn = t_duplicate;
			return;
		}
	}

	for (int i=0; i<strlen(incorrect); i++){
		if (tolower(key) == incorrect[i]){
			turn = t_duplicate;
			return;
		}
	}

	bool found = false;
	for (int i=0; i<strlen(word); i++){
		//Compare guess char with the key pressed
		if (tolower(word[i]) == tolower(key)){
			//Replace guess letter with actual letter if guessed correct
			guess[i] = word[i];
			turn = t_correct;
			found = true;
		}
	}
	if (!found){
		

	for (int i=0; i<strlen(incorrect); i++){
		if (incorrect[i] == '_'){
			incorrect[i] = tolower(key);
			turn = t_incorrect;
			return;
		}
	}
	}
}

int guesses_incorrect(){
	int guesses = 0;
	for (int i=0; i<strlen(incorrect); i++){
		if (incorrect[i] != '_'){
			guesses++;
		}
	}
	return guesses;
}
int guesses_correct(){
	int guesses = 0;
	for (int i=0; i<strlen(guess); i++){
		if (guess[i] != '_'){
			guesses++;
		}
	}
	return guesses;
}    // Show current level