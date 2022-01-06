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

using namespace std;

enum Permissions { NONE, TEACHER_PERMS, ADMIN_PERMS };
enum MenuOptions { LOGIN = 1, REGISTER, CREATE_TEST_USER, STUDENT_RECORDS, ADMIN_SCREEN, LOGOUT,  QUIT= 'q' };
enum Type { STUDENT = 1, PARENT, TEACHER, ADMIN };

void displayMenu(int, bool); 
int chooseType(); // Choose type from Student, Parent, Teacher and Admin.
int getPermissions(int); // Fetch permissions based on which type has been chosen.
void printDots(); // Prints ... (full-stop) with a slight delay inbetween each.

int loginAsType();
int registerAsType();
void studentRecordsAsType(int);
void adminScreen();

// v Temporary functions used for testing purposes. Will be removed later.
int createTestUserOfType();
void createTestUser(Student&);
void createTestUser(Parent& user);
void createTestUser(Teacher& user);
void createTestUser(Admin& user);

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

		else if (iInput == CREATE_TEST_USER)
			chosenType = createTestUserOfType();

		else if (iInput == STUDENT_RECORDS)
			if (permissions >= TEACHER_PERMS)
				studentRecordsAsType(chosenType);
			else {
				cout << "Invalid input";
				printDots();
			}
		else if (iInput == ADMIN_SCREEN && permissions >= ADMIN)
			adminScreen();

		else if (iInput == LOGOUT && loggedIn)
		{
			loggedIn = false;
			chosenType = 0;
			cout << "Logging '" << user.username << "' out";
			printDots();
		}

		else if (tolower(cInput) == QUIT) {
			menuLoop = false;
		}

	} while (menuLoop);
}

int loginAsType() {

	system("CLS");
	cout << "Choose what you want to log in as: " << endl;
	int chosenType = chooseType();
	bool invalidInput = false; 

	do
	{
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
int createTestUserOfType() {
	system("CLS");
	bool invalidInput = false;
	int chosenType;

	do
	{
		cout << "Choose type to create:" << endl;
		chosenType = chooseType();

		if (chosenType == STUDENT) {
			createTestUser(student);
			user = student.personalDetails;
			loggedIn = true;
		}
		else if (chosenType == PARENT) {
			createTestUser(parent);
			user = parent.personalDetails;
			loggedIn = true;
		}
		else if (chosenType == TEACHER) {
			createTestUser(teacher);
			user = teacher.personalDetails;
			loggedIn = true;
		}
		else if (chosenType == ADMIN) {
			createTestUser(admin);
			user = admin.personalDetails;
			loggedIn = true;
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
	cout << "User created";
	printDots();

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

}

void createTestUser(Student& user)
{
	Person person = { "FirstName","MiddleName","LastName","Gender", "BirthDate","EmailAddress","0 1234-567 89","studUsername","studPass" };
	user.personalDetails = person;
}
void createTestUser(Parent& user)
{
	Person person = { "FirstName","MiddleName","LastName","Gender", "BirthDate","EmailAddress","0 1234-567 89","parentUsername","parentPass" };
	user.personalDetails = person;
}
void createTestUser(Teacher& user)
{
	Person person = { "FirstName","MiddleName","LastName","Gender", "BirthDate","EmailAddress","0 1234-567 89","teacherUsername","teacherPass" };
	user.personalDetails = person;
}
void createTestUser(Admin& user)
{
	Person person = { "FirstName","MiddleName","LastName","Gender", "BirthDate","EmailAddress","0 1234-567 89","adminUsername","adminPass" };
	user.personalDetails = person;
}

void displayMenu(int perms, bool loggedIn) {
	int menuItemsCount = 1;

	cout << "\n\t" << menuItemsCount << ". Login" << endl;
	menuItemsCount++;

	cout << "\t" << menuItemsCount << ". Register" << endl;
	menuItemsCount++;

	cout << "\t" << menuItemsCount << ". Create test user" << endl;
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

	do
	{
		cin >> input;
		if (input > 4 && input < 1) {
			cout << "Invalid input";
			printDots();
			invalidChoice = true;
		}
		else
			invalidChoice = false;
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

	std::cout << ".";
	sleep_for(200ms);
	std::cout << ".";
	sleep_for(200ms);
	std::cout << ".\n\n";
	sleep_for(200ms);
}
