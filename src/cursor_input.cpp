#include "cursor_input.hpp"
#include <iostream>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

InputKey getInputKey() {
#ifdef _WIN32
    int ch = _getch();

    if (ch == 0 || ch == 224) {
        switch (_getch()) {
            case 72: return InputKey::UP;
            case 80: return InputKey::DOWN;
            case 75: return InputKey::LEFT;
            case 77: return InputKey::RIGHT;
            default: return InputKey::NONE;
        }
    } else {
        switch (ch) {
            case 13: return InputKey::ENTER;
            case 27: return InputKey::ESC;
            case 'r':
            case 'R': return InputKey::R;
            case 'z':
            case 'Z': return InputKey::Z;
            default: return InputKey::NONE;
        }
    }
#else
    // Unix/Linux support can be added here if needed
    return InputKey::NONE;
#endif
}

void playSound(SoundEffect effect) {
#ifdef _WIN32
    switch (effect) {
        case CLICK:   Beep(600, 40); break;
        case VICTORY: Beep(1000, 200); Beep(1200, 200); break;
        case DEFEAT:  Beep(400, 300); break;
    }
#else
    cout << "\a"; // fallback sound
#endif
}

void toggle_cursor(bool showFlag) {
#ifdef _WIN32
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
#else
    if (showFlag)
        cout << "\033[?25h";
    else
        cout << "\033[?25l";
#endif
}

char get_input_char() {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}
