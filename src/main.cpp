#include <iostream>
#include "menu.hpp"
#include "cursor_input.hpp"
#include "ultils.hpp"

using namespace std;

int main(){

	//Setup console
	toggle_cursor(false);
	// console_size(800,600);

	//Loop game forever
	while(1){
		menu();
    }

	return 1;
}