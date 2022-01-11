#include <iostream>
#include <thread>
#include <sstream>

#include "Menu.h"
#include "Login.h"
#include "Structures.h"
#include "Introduction.h"
#include "Registration.h"
#include "StorageHandling.h"
#include "StudentRecords.h"
#include "Admin.h"

using namespace std;

enum Permissions { NONE, TEACHER_PERMS, ADMIN_PERMS };
enum MenuOptions { LOGIN = 1, REGISTER, STUDENT_RECORDS, ADMIN_SCREEN, LOGOUT,  QUIT= 'q' };
enum Type { STUDENT = 1, PARENT, TEACHER, ADMIN };

void displayMenu(int, bool); 
int chooseType(); // Choose type from Student, Parent, Teacher and Admin.
int getPermissions(int); // Fetch permissions based on which type has been chosen.
void printDots(); // Prints ... (full-stop) with a slight delay inbetween each.

int loginAsType();
int registerAsType();
void studentRecordsAsType(int);
void adminScreen();

Person user; // Used to display logged-in users information.
Student student;
Parent parent;
Teacher teacher;
Admin admin;
bool loggedIn = false;

void menu() 
{
	int permissions = 0;
	int chosenType = 0;
	bool menuLoop = true;

	do 
	{
		permissions = getPermissions(chosenType);

		system("CLS");

		introduction();
		displayMenu(permissions, loggedIn);

		char cInput;
		int iInput;

		cin >> cInput;
		cin.ignore();
		iInput = cInput - '0'; // Converts the input of type char to int.
		
		if (iInput == LOGIN)
			chosenType = loginAsType();

		else if (iInput == REGISTER)
			chosenType = registerAsType();

		else if (iInput == STUDENT_RECORDS && permissions >= TEACHER_PERMS)
			studentRecordsAsType(chosenType);

		else if (iInput == ADMIN_SCREEN && permissions >= ADMIN_PERMS)
			adminMenu();

		else if (iInput == LOGOUT && loggedIn) {
			loggedIn = false;
			chosenType = 0;
			cout << "Logging '" << user.username << "' out";
			printDots();
		}
		else if (tolower(cInput) == QUIT) {
			menuLoop = false;
		}
		else {
			cout << "Invalid input";
			printDots();
		}

	} while (menuLoop);
}

int loginAsType() {

	system("CLS");
	int chosenType;
	bool invalidInput = false; 

	do
	{
		cout << "Choose what you want to log in as: " << endl;
		chosenType = chooseType();

		if (chosenType == STUDENT) {
			loggedIn = login(student);
		}
		else if (chosenType == PARENT) {
			loggedIn = login(parent);
		}
		else if (chosenType == TEACHER) {
			loggedIn = login(teacher);
		}
		else if (chosenType == ADMIN) {
			loggedIn = login(admin);
		}
		
		if (chosenType >= STUDENT && chosenType <= ADMIN)
			invalidInput = false;
		else
		{
			cout << "Invalid input";
			printDots();
			system("CLS");
			invalidInput = true;
		}
	} while (invalidInput);
	return chosenType;
}
int registerAsType() {
	system("CLS");
	cout << "Choose what you want to register as:" << endl;
	int chosenType = chooseType();
	bool invalidInput = false;

	do
	{
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
		if (chosenType >= STUDENT && chosenType <= ADMIN)
			invalidInput = false;
		else
		{
			cout << "Invalid input";
			printDots();
			system("CLS");
			invalidInput = true;
		}

	} while (invalidInput);
	return chosenType;
}
void studentRecordsAsType(int chosenType) {
	if (chosenType == TEACHER) {
		studentRecords(teacher);
	}
	else if (chosenType == ADMIN) {
		studentRecords(admin);
	}
}
void adminScreen() {
	adminMenu();
}

void displayMenu(int perms, bool loggedIn) {
	int menuItemsCount = 1;

	cout << "\n\t" << menuItemsCount << ". Login" << endl;
	menuItemsCount++;

	cout << "\t" << menuItemsCount << ". Register" << endl;
	menuItemsCount++;

	cout << "\t" << menuItemsCount << ". Student Records";
	if (perms < TEACHER_PERMS)
		cout << " - Not enough permissions.";
	cout << endl;
	menuItemsCount++;

	cout << "\t" << menuItemsCount << ". Admin Screen";
	if (perms < ADMIN_PERMS)
		cout << " - Not enough permissions.";
	cout << endl;
	menuItemsCount++;

	if (loggedIn) {
		cout << "\t" << menuItemsCount << ". Log out" << endl;
		menuItemsCount++;
	}
	cout << "\tQ. Quit" << endl;
}
int chooseType() {
	bool invalidChoice = false;
	int input;

	cout << "1. Student" << endl
		<< "2. Parent" << endl
		<< "3. Teacher " << endl
		<< "4. Admin" << endl;

	do {
		cin >> input;
		cin.clear();
		cin.ignore();

		if (input >= 1 && input <= 4) 
			invalidChoice = false;
		
		else {
			cout << "Invalid input";
			printDots();
			invalidChoice = true;
		}
			
	} while (invalidChoice);
	return input;
}
int getPermissions(int chosenType) {
	if (chosenType == TEACHER)
		return TEACHER_PERMS;
	else if (chosenType == ADMIN)
		return ADMIN_PERMS;
	else
		return 0;
}

void printDots() {
	using namespace std::this_thread;
	using namespace std::chrono_literals;

	sleep_for(200ms);
	std::cout << ".";
	sleep_for(200ms);
	std::cout << ".";
	sleep_for(200ms);
	std::cout << ".\n\n";
	sleep_for(200ms);
}
