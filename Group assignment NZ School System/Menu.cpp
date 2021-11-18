#include <iostream>

#include "Menu.h"
#include "Structures.h"
#include "Login.h"
#include "Registration.h"
#include "StorageHandling.h"

using namespace std;

enum Permissions { NONE, TEACHER, ADMIN };
enum MenuOptions { LOGIN = 1, REGISTER, STUDENT_RECORDS, QUIT = 'q' };
enum Type { STUDENT = 1, PARENT, TEACHER, ADMIN };

void displayMenu(int);
int chooseType();

void menu() 
{
	int permissions = 0;
	int chosenType;

	Student student;
	Parent parent;
	Teacher teacher;
	Admin admin;

	do 
	{
		displayMenu(permissions);
		char input;

		cin >> input;
		cin.ignore();
		
		system("CLS");
		if (input == LOGIN) 
		{
			cout << "Choose what you want to log in as: " << endl;
			chosenType = chooseType();

			if (chosenType == STUDENT)
				login(student);
			else if (chosenType == PARENT)
				login(parent);
			else if (chosenType == TEACHER)
				login(teacher);
			else if (chosenType == ADMIN)
				login(admin);
		}
		else if (input == REGISTER) 
		{
			cout << "Choose what you want to register as:" << endl;
			chosenType = chooseType();

			if (chosenType == STUDENT) {
				registerUser(student);
				saveToFile(student);
			}
			else if (chosenType == PARENT) {
				registerUser(parent);
				saveToFile(parent);
			}
			else if (chosenType == TEACHER) {
				registerUser(teacher);
				saveToFile(teacher);
			}
			else if (chosenType == ADMIN) {
				registerUser(admin);
				saveToFile(admin);
			}
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
int chooseType() {
	bool invalidChoice = false;
	int input;

	cout << "1. Student" << endl
		<< "2. Parent" << endl
		<< "3. Teacher " << endl
		<< "4. Admin" << endl;

	do
	{
		cin >> input;
		if (input > 4 && input < 1) {
			cout << "Invalid input." << endl;
			invalidChoice = true;
		}
		else
			return input;
	} while (invalidChoice);
}