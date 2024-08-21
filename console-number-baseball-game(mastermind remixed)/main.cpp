/*
	Author: Daniel Lee
	Last Update: May 15, 2017
	Program Description: Please read "ReadMe.txt"

	Bug Report
	Case 1. When user enters a space in between numbers, it generates the error emssage twice in a row

*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "UI.h"

using namespace std;

const static int MAX_SIZE = 4;
const static int MAX_NUM_DIGIT = 10;

// Function Declarations
void display_number_of_(int[], int);
bool check_input(string, int);
void display_condition_of_(int[], int[], int, int); // user[], com[], max_size, round
bool is_num_found(int[], int[], int); // user[], com[], max_size
bool start_new_game(char);
void bring_the_game(int, int); // level, max_number_of_round

void main() {
	UI ui;
	int user_level = 0;
	int max_round = 10;
	char user_more_game;

	srand(time(NULL));

	do {

		ui.display_menu();
		cout << "\t>>";
		cin >> user_level;

		while (user_level != 1 && user_level != 2 && user_level != 3) {
			ui.display_error_message();
			cin >> user_level;
		}

		switch (user_level) {
		case 1:
			max_round = 10;
			bring_the_game(user_level, max_round);
			break;
		case 2:
			max_round = 8;
			bring_the_game(user_level, max_round);
			break;
		case 3:
			max_round = 6;
			bring_the_game(user_level, max_round);
			break;
		default:
			break;
			// do nothing
		}

		cout << "Do you want to play again? (Y/N): ";
		cin >> user_more_game;
		system("cls");
	} while (start_new_game(user_more_game));

	cout << "BYE !" << endl;

} // closure of main()

void bring_the_game(int user_custom_num_round, int MAX_ROUND) {
	UI ui;
	int nums[MAX_NUM_DIGIT] = { 0,1,2,3,4,5,6,7,8,9 };
	int round = 0;
	int temp_value;
	bool more_game = false;
	bool user_won = false;
	int computer_num[MAX_SIZE];
	int user_num[MAX_SIZE];
	char ch;
	string response;

	// Generate a non-repetitive number		
	//shuffle nums[] array
	for (int i = MAX_NUM_DIGIT - 1; i > 0; --i)
	{
		//get swap index
		int j = rand() % i;
		//swap p[i] with p[j]
		int temp = nums[i];
		nums[i] = nums[j];
		nums[j] = temp;
	}

	//copy first n elements from p to arr
	for (int i = 0; i < MAX_SIZE; ++i)
		computer_num[i] = nums[i];

	//display_number_of_(computer_num, MAX_SIZE);

	cout << endl;
	cout << "\t##  You have only [" << MAX_ROUND << "] guess to win ##" << endl;
	cout << endl;
	cout << "\t######################################" << endl;
	cout << "\t#####           SUMMARY          #####" << endl;

	while (round < MAX_ROUND) {
		cout << "\t######################################" << endl;
		cout << endl;
		cout << "\t  Guess: ";
		cin >> response;

		while (!check_input(response, MAX_SIZE)) {
			cout << endl;
			ui.display_error_message();
			cin >> response;
		}

		cout << endl;

		// convert user's response(string) to integer value
		for (int j = 0; j < MAX_SIZE; j++) {
			ch = response.at(j);
			user_num[j] = ch - '0'; // convert char to int
		}

		display_condition_of_(user_num, computer_num, MAX_SIZE, round);

		// check if user guessed all digits before reaching to max num of rounds
		if (is_num_found(user_num, computer_num, MAX_SIZE)) {
			ui.display_victory_message();
			user_won = true;
			break;
		}
		round++;
	}

	if (!user_won) {
		cout << "\t######################################" << endl;
		cout << "\t##     Sorry! The number was [";
		display_number_of_(computer_num, MAX_SIZE);
		cout << "]   ##" << endl;
		cout << "\t######################################" << endl;
	}
	cout << endl;
}

// This function checks if user wants to play more game
bool start_new_game(char ch) {
	return (ch == 'Y' || ch == 'y');
}

// This function checks if user has found the computer's number 
bool is_num_found(int user[], int com[], int size) {

	int num_strike = 0;

	// checks conditions for strike only
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j && user[i] == com[j]) {
				num_strike++;
			}
		}
	}
	return (num_strike == 4);
}

// This function compares user's guess to computer's number and displays a condition to user 
void display_condition_of_(int user[], int com[], int size, int round) {
	// global vars
	int num_ball = 0;
	int num_strike = 0;
	int num_out = 0;
	bool match_found = true; // 1 computer digit checks 4 user digits

	for (int i = 0; i < size; i++) {
		match_found = true;

		for (int j = 0; j < size; j++) {
			if (i == j && user[i] == com[j]) {
				num_strike++;
				match_found = true;
			}
			if (i != j && user[i] == com[j]) {
				num_ball++;
				match_found = true;
			}
		}
	}

	num_out = size - num_strike - num_ball; // there are only 4 digits

	if (round == 0)
		cout << "\t  (" << round + 1 << "st Round Result)==" << "[ " << num_strike << "S  " << num_ball << "B  " << num_out << "O" << " ]" << endl;
	else if (round == 1)
		cout << "\t  (" << round + 1 << "nd Round Result)==" << "[ " << num_strike << "S  " << num_ball << "B  " << num_out << "O" << " ]" << endl;
	else if (round == 2)
		cout << "\t  (" << round + 1 << "rd Round Result)==" << "[ " << num_strike << "S  " << num_ball << "B  " << num_out << "O" << " ]" << endl;
	else
		cout << "\t  (" << round + 1 << "th Round Result)==" << "[ " << num_strike << "S  " << num_ball << "B  " << num_out << "O" << " ]" << endl;
	cout << endl;
}

// This function checks for validity of user's input, str
bool check_input(string str, int size) {
	char first_ch;

	if (str.size() != size) // size doesn't match
		return false;
	else {
		for (int i = 0; i < size; i++) {
			first_ch = str.at(i);

			if (!(first_ch >= '0' || first_ch <= '9')) // if not a number
				return false;
		}
	}
	return true;
}

// This fucntion displays the number of a given int array
void display_number_of_(int a[], int size) {

	for (int i = 0; i < size; i++) {
		cout << a[i];
	}
}