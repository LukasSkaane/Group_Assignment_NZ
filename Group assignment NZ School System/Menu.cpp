#include <iostream>

#include "Menu.h"

using namespace std;

enum Permissions{NONE, TEACHER, ADMIN };
enum MenuOptions{LOGIN=1, REGISTER, STUDENT_RECORDS, QUIT='q' };

void displayMenu(int);

int getMenuChoice(int perms) {
	do {
		displayMenu(perms);
		char input;

		cin >> input;
		cin.ignore();
		switch (input)
		{
		case LOGIN:
			return 1;
			break;
		case REGISTER:
			return 2;
			break;
		case STUDENT_RECORDS:
			return 3;
			break;
		case QUIT:
			return -1;
			break;
		default:
			cout << "Invalid input" << endl;
			break;
		}
	} while (false);
}

void displayMenu(int perms) {
	cout << "\n\t1. Login" << endl
		<< "\t2. Register" << endl;

	if (perms <= TEACHER)
		cout << "\t3. Student Records" << endl;
	if (perms <= ADMIN)
		cout << "\t4. Admin Screen" << endl;
	cout << "\tQ. Quit" << endl;
}