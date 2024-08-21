#include "UI.h"
#include <iostream>

using namespace std;

UI::UI() {

}

void UI::display_menu() {
		cout << endl;
		cout << "\t######################################" << endl;
		cout << "\t#  WECLOME TO NUMBER BASEBALL GAME!  #" << endl;
		cout << "\t######################################" << endl;
		cout << "\t#      PLEASE SELECT AN OPTION       #" << endl;
		cout << "\t######################################" << endl;
		cout << "\t#           1. BEGINNER              #" << endl;
		cout << "\t#           2. INTERMEDIATE          #" << endl;
		cout << "\t#           3. PRO                   #" << endl;
		cout << "\t######################################" << endl;
		cout << endl;
	}

void UI::display_error_message() {
	cout << "\t  [" << "!" << "] " << "Invalid input was entered!" << endl;
	cout << "\t  please enter again : ";
}

void UI::display_victory_message() {
	cout << "\t######################################" << endl;
	cout << "\t##       YES!  YOU ARE CORRECT!     ##" << endl;
	cout << "\t######################################" << endl;
}