#pragma once

#include <iostream>
#include <string>

using namespace std;

void clearScreen();
void clearTerminal(); // Full terminal reset
void setTextColor(int color);
void hideCursor();
int getch();    // For key input
bool kbhit();   // For non-blocking keyboard input

void console_size(int width, int height);
void sleep_ms(int ms);
int random_range(int min, int max);

// Box drawing characters (UTF-8)
extern const char SYMBOL_HORIZONTAL[];
extern const char SYMBOL_VERTICAL[];
extern const char SYMBOL_TOP_LEFT[];
extern const char SYMBOL_TOP_RIGHT[];
extern const char SYMBOL_BOTTOM_LEFT[];
extern const char SYMBOL_BOTTOM_RIGHT[];
extern const char SYMBOL_T_LEFT[];
extern const char SYMBOL_T_RIGHT[];
extern const char SYMBOL_T_TOP[];
extern const char SYMBOL_T_BOTTOM[];
extern const char SYMBOL_INTERSECT[];