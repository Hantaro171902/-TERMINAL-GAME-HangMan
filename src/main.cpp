#include <iostream>
#include "game_logic.hpp"
#include "cursor_input.hpp"
#include "words.hpp"
#include "ultils.hpp"

using namespace std;

int main() {
    // Setup
    load_word_data();
    start_game(4, 8, 2, WordTheme::t_animals);  // test with 'animals'

    // Input loop
    while (true) {
        // Redraw UI
        clearScreen();
        print_level();

        // Input
        InputKey key = getInputKey();
        if (key == InputKey::ESC) break;

        if (key == InputKey::ENTER) {
            // Maybe confirm guess or restart?
        } else {
            char ch = get_input_char(); // Get a single character
            if (isalpha(ch)) {
                guess_char(tolower(ch));
            }
        }

        refresh_status();
        refresh_turn();

        // End condition
        if (guesses_incorrect() >= 6) {
            cout << "You lost!" << endl;
            break;
        }

        if (guesses_correct() == 6) {
            cout << "You won!" << endl;
            break;
        }

        sleep_ms(100);
    }

    cout << "\nThanks for playing!" << endl;
    return 0;
}
