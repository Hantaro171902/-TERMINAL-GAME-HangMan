#include "menu.hpp"
#include "ultils.hpp"
#include "cursor_input.hpp"
#include "game_logic.hpp"

static int stage = 0;
static int selected = 0;

static int difficulty = -1;
static int theme = -1;

void menu() {
	while (true) {
		print_menu();

		InputKey key = getInputKey();

		switch (key) {
			case InputKey::ESC:
				exit(0);
			case InputKey::UP:
				if (selected > 0) selected--;
				break;
			case InputKey::DOWN:
				if ((stage == 0 && selected < 2) || (stage == 1 && selected < 4)) selected++;
				break;
			case InputKey::ENTER:
				if (stage == 0) {
					difficulty = selected;
					stage++;
					selected = 0;
				} else if (stage == 1) {
					theme = selected;
					stage++;
					selected = 0;
				}
				break;
			default:
				break;
		}

		// Start game once both selected
		if (difficulty != -1 && static_cast<WordTheme>(theme) != -1) {
			print_load();
			sleep_ms(300);

			switch (difficulty) {
				case 0: start_game(3, 5, 0,  static_cast<WordTheme>(theme)); break;
				case 1: start_game(6, 8, 1,  static_cast<WordTheme>(theme)); break;
				case 2: start_game(9, 20, 2,  static_cast<WordTheme>(theme)); break;
			}

			// Reset for next loop
			stage = 0;
			selected = 0;
			difficulty = -1;
			theme = -1;
		}
	}
}

void print_option(const string& label, bool isSelected) {
	cout << "  [" << (isSelected ? "*" : " ") << "]\t" << label << endl;
}

void print_menu() {
	clearScreen();

	cout << "-----------------------------Press Escape to quit-------------------------------" << endl;
	cout << R"(   _   _                  ___  ___            
                | | | |                 |  \/  |            
                | |_| | __ _ _ __   __ _| .  . | __ _ _ __  
                |  _  |/ _` | '_ \ / _` | |\/| |/ _` | '_ \ 
                | | | | (_| | | | | (_| | |  | | (_| | | | |
                \_| |_/\__,_|_| |_|\__, \_|  |_/\__,_|_| |_|
                                    __/ |                   
                                    |___/                    )" << endl;

	if (stage == 0) {
		cout << "\n--------------Please choose a difficulty using the arrow keys-------------------\n\n";
		print_option("Easy (3-5 letters)", selected == 0);
		print_option("Medium (6-8 letters, 1 given)", selected == 1);
		print_option("Hard (8+ letters, 2 given)", selected == 2);
	} else if (stage == 1) {
		cout << "\n-----------------Please choose a theme using the arrow keys---------------------\n\n";
		print_option("Animals", selected == 0);
		print_option("Countries", selected == 1);
		print_option("Fruits", selected == 2);
		print_option("Periodic Elements", selected == 3);
		print_option("US States", selected == 4);
	}

	cout << "\n\n--------------------------------------------------------------------------------" << endl;
}

void print_load() {
	clearScreen();

	cout << "-----------------------------Press Escape to quit-------------------------------" << endl;
	cout << R"(   _   _                  ___  ___            
                | | | |                 |  \/  |            
                | |_| | __ _ _ __   __ _| .  . | __ _ _ __  
                |  _  |/ _` | '_ \ / _` | |\/| |/ _` | '_ \ 
                | | | | (_| | | | | (_| | |  | | (_| | | | |
                \_| |_/\__,_|_| |_|\__, \_|  |_/\__,_|_| |_|
                                    __/ |                   
                                    |___/                    )" << endl;
	cout << "\n--------------------------Loading, please wait...-------------------------------\n\n";
}

