// cursor_input.cpp
#include "cursor_input.hpp"
#include "ultils.hpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>     // for read()
#include <fcntl.h>      // for fcntl()

using namespace std;

#ifdef _WIN32
#include <windows.h>
void toggle_cursor(bool showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}
#else
void toggle_cursor(bool showFlag){
    // Use ANSI escape for *nix
    if (showFlag)
        std::cout << "\033[?25h"; // show cursor
    else
        std::cout << "\033[?25l"; // hide cursor
}

void move_cursor(int x, int y){
    cout << "\033[" << y << ";" << x << "H";
}

// Helper struct to ensure that terminal is repaired
struct terminal_state {
    struct termios oldt;
    int oldf;
    terminal_state() {
        tcgetattr(STDIN_FILENO, &oldt); 
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0); 
    }

    ~terminal_state() {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
    }
};

#endif


char get_input_char() {
    char buf = 0;
#ifndef _WIN32
    
    terminal_state restorer;
    struct termios new_one = restorer.oldt; 
    new_one.c_lflag &= ~ICANON; 
    new_one.c_lflag &= ~ECHO;  // Turn off echo
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_one) < 0) perror("tcsetattr ICANON");
#endif

    if (read(STDIN_FILENO, &buf, 1) < 0) perror("read()");

#ifdef _WIN32
    
#endif
    return buf;
}

InputKey getInputKey() {
#ifndef _WIN32
    
    terminal_state restorer;
    struct termios newt = restorer.oldt; 

    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set read() to non-blocking mode
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
#endif

    InputKey key = InputKey::NONE;
    char ch;

    while (true)
    {
        if (read(STDIN_FILENO, &ch, 1) == 1) { // Arrow key escape sequence
            if (ch == '\033') {
                char seq[2];
                if (read(STDIN_FILENO, &seq[0], 1) == 1 && 
                    read(STDIN_FILENO, &seq[1], 1) == 1) {
                    switch (seq[1]) {
                        case 'A': return InputKey::UP;
                        case 'B': return InputKey::DOWN;
                        case 'C': return InputKey::RIGHT;
                        case 'D': return InputKey::LEFT;
                    }
                }
            } else {
                switch (ch) {
                    case 'w': case 'W': return InputKey::UP;
                    case 's': case 'S': return InputKey::DOWN;
                    case 'a': case 'A': return InputKey::LEFT;
                    case 'd': case 'D': return InputKey::RIGHT;
                    case '\n': return InputKey::ENTER;
                    case 27:   return InputKey::ESC; // Escape
                    case 'q': case 'Q': return InputKey::Q; // Quit to menu
                    case 'r': case 'R': return InputKey::R; // Restart game
                    case 'z': case 'Z': return InputKey::Z; // Undo
                    
                    default:   return InputKey::NONE;
                }
            }

            if (key != InputKey::NONE) {
                break;
            }

        }
        usleep(1000); // Sleep for a short time to avoid busy waiting
    }

    // tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore original settings
    // fcntl(STDIN_FILENO, F_SETFL, 0); // Restore blocking mode
    
    return key;
}

void playSound(SoundEffect effect) {
    switch (effect) {
        case CLICK:   system("aplay sounds/click.wav &"); break;
        case VICTORY: system("aplay sounds/victory.wav &"); break;
        case DEFEAT:  system("aplay sounds/defeat.wav &"); break;
    }
}

