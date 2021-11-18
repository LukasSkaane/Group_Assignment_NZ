#include <fstream>
#include <string>
#include <iostream>

#include "Structures.h"
#include "StorageHandling.h"

using namespace std;

void login(Student&); /// This is what the login function should look like, since passing structures as references is a good, memory-efficient practice. 
void login(Parent&); /// I point this out because I previously said that they should return their respective types, but this is a better solution. :)
void login(Teacher&);
void login(Admin&);  
// ^^^^ This is called overloading, when multiple functions have the same name but different signatures (aka different input arguments).
// Arthur went over it at some point. Its a good, but easy name to forget :)

// Here are a few things that might come in handy when you're re-writing the login.cpp
void exampleForMohamed() {
	vector<string> usernames; // vector of type string for storing a list of usernames.
	getUsernames(usernames); // This will add all usernames stored in all files to this vector. 
							 // (It is included with '#include "StorageHandling.h"' at the top.)
							 // (It will NOT remove any existing usernames already in the list.)

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

	string username, password, un, pw;
	int menu_option;
	do {
		cout << "LOGIN PAGE - *******************";
		cout << "\n 1. LOG-IN AS STUDENT";
		cout << "\n 2. LOG-IN AS PARENT";
		cout << "\n 3. LOG-IN AS TEACHER";
		cout << "\n 4. EXIT";

		cout << "\n\n Enter your option: ";
		cin >> menu_option;

		switch (menu_option)
		{
		case 1:
			cout << "LOGIN AS STUDENT";
			cout << "****************";
			cout << "Enter UserName :   "; cin >> username;
			cout << "Enter PassWord :   "; cin >> password;


			read.open("data\\" + username + ".txt");
			getline(read, un);
			getline(read, pw);

			if (un == username && pw == password)
			{
				return true;
			}
			else
			{
				return false;
			}

			break;
		case 2:
			cout << " LOGIN AS PARENT";
			cout << "****************";
			cout << "Enter UserName :   ";
			cin >> username;
			cout << "Enter PassWord :   ";
			cin >> password;


			read.open("data\\" + username + ".txt");
			getline(read, un);
			getline(read, pw);

			if (un == username && pw == password)
			{
				return true;
			}
			else
			{
				return false;
			}

			break;
		case 3:
			cout << " LOGIN AS TEACHER";
			cout << "****************";
			cout << "Enter UserName :   "; cin >> username;
			cout << "Enter PassWord :   "; cin >> password;


			read.open("data\\" + username + ".txt");
			getline(read, un);
			getline(read, pw);

			if (un == username && pw == password)
			{
				return true;
			}
			else
			{
				return false;
			}


			break;
		case 4:
			exit(0);
			break;

		default:
			cout << "Sorry incorrect option entered in menu";
			break;



		}
	} while (true);
	system("CLS");


}