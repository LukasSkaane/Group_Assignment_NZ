#include <fstream>
#include <string>
#include <iostream>
#include <vector>


#include "Structures.h"
#include "StorageHandling.h"
#include "Login.h"


using namespace std;

bool loginS(); /// This is what the login function should look like, since passing structures as references is a good, memory-efficient practice. 
bool loginP(); /// I point this out because I previously said that they should return their respective types, but this is a better solution. :)
bool loginT();
bool loginA();  
bool isUsernameValid(string Username);
int a;
Teacher p;
// ^^^^ This is called overloading, when multiple functions have the same name but different signatures (aka different input arguments).
// Arthur went over it at some point. Its a good, but easy name to forget :)

// Here are a few things that might come in handy when you're re-writing the login.cpp
void exampleForMohamed() {
	vector<string> usernames; // vector of type string for storing a list of usernames.
	getUsernames(usernames); // This will add all usernames stored in all files to this vector. 
							 // (It is included with '#include "StorageHandling.h"' at the top.)
							 // (It will NOT remove any existing usernames already in the list.)

	char password[51];

	std::cout << "input password: ";
	std::cin >> password;

	bool usernamesExists = false;
	for (string x : usernames) {
		if (x == password) {
			usernamesExists = true;
		}
	}


	vector<Student> students; // vector of type Student for storing a list of Students.
	getStudents(students);	// This will add all students stored in the "savedStudents.dat" file.
							// (It is included with '#include "StorageHandling.h"' at the top.)
							// (It will NOT remove any existing usernames already in the list.)
	
	// You can look in "Structures.h" for how to access username/password as well as other variables inside the structs, or ask me if you're unsure.

	// For the other types its as simple as:
	vector<Parent> parents;
	getParents(parents);

	// And so on...
						
	/// All the stuff about choosing what type of user you want to login as is chosen in Menu.cpp, So you "only" need to write the code to actually log in to a specific user type.
	/// 
}

bool saveStudentToFile();
bool saveParentToFile();
bool loginAsTeacher()
{
	ifstream read;

	
	int menu_option;
	bool invalidUsername = false;

	bool usernameExists;
	bool passwordExists;

	do {
		std::cout << "LOGIN PAGE - *******************";
		std::cout << "\n 1. LOG-IN AS STUDENT";
		std::cout << "\n 2. LOG-IN AS PARENT";
		std::cout << "\n 3. LOG-IN AS TEACHER";
		std::cout << "\n 4. EXIT";

		std::cout << "\n\n Enter your option: ";
		std::cin >> menu_option;

		switch (menu_option)
		{
		case 1:
			loginS();
			break;
		case 2:
			loginP();
			break;
		case 3:
			loginT();
			break;
		case 4:
			exit(0);
			break;

		default:
			std::cout << "Sorry incorrect option entered in menu";
			break;



		}
	} while (true);
	std::system("CLS");


}

char username[51], password[51], un[51], pw[51];
vector<string> usernames;
vector<string> passwords;


bool loginS()
{
	char username[51], password[51], un[51], pw[51];
	vector<string> usernames;
	vector<string> passwords;

	cout << "LOGIN AS STUDENT";
	cout << "****************";
	cout << "Enter UserName :   ";
	cin >> username;
	bool usernameExists = false;
	for (string x : usernames)
	{
		if (x == username) {
			usernameExists = true;
		}
	}

	cout << "Enter PassWord :   ";
	cin >> password;
	bool passwordExists = false;
	for (string x : passwords)
	{
		if (x == password) {
			passwordExists = true;
		}
	}

	if (un == username && pw == password)
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool loginP()
{
	cout << " LOGIN AS PARENT";
	cout << "****************";
	cout << "Enter UserName :   ";
	cin >> username;
	bool usernameExists = false;
	for (string x : usernames)
	{
		if (x == username) {
			usernameExists = true;
		}
	}
	cout << "Enter PassWord :   ";
	cin >> password;
	bool passwordExists = false;
	for (string x : passwords)
	{
		if (x == password) {
			passwordExists = true;
		}
	}




	if (un == username && pw == password)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool loginT()
{
	cout << " LOGIN AS TEACHER";
	cout << "****************";
	cout << "Enter UserName :   ";
	cin >> username;
	bool usernameExists = false;
	for (string x : usernames)
	{
		if (x == username) {
			usernameExists = true;
		}
	}
	cout << "Enter PassWord :   ";
	cin >> password;
	cin >> password;
	bool passwordExists = false;
	for (string x : passwords)
	{
		if (x == password) {
			passwordExists = true;
		}
	}




	if (un == username && pw == password)
	{
		return true;
	}
	else
	{
		return false;
	}


}