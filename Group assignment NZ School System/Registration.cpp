#include <iostream>
#include <string>
#include <iomanip>
#include <array>
#include <algorithm>

#include "Registration.h"
#include "Structures.h"
#include "StorageHandling.h"

using namespace std;

const array<char, 3> invalidPasswordChars = { '\\', '\'', '\"'}; 
// Disallowing back-slash (\), single-quote ('), double-quote (") because I believe incorrect handling would result in an untraceable exception. (I'd rather not try to debug that)
vector<string> usernames;

void createPersonalDetails(Person&);
void registerUser(Student&);
void registerUser(Parent&);
void registerUser(Teacher&);
void registerUser(Admin&); // Incomplete

vector<char[]> addLessons(); 
// ^As of now does not work, I am unsure how to save a 
// list of student classes so will wait before adding this functionality.
int setStudentId();
bool isPasswordValid(string);
bool isUsernameValid(string);


void registerUser(Student& student) 
{
	cout << "Set personal details for student." << endl;
	createPersonalDetails(student.personalDetails);
	student.studentId = setStudentId();
	//student.classesList = addLessons();
	// setCaregiver(student.caregiverPrimary);
	// Ask to set secondary caregiver setCaregiver(student.caregiverSecondary);
}
//vector<char[]> addLessons() 
//{
//	vector<char[]> lessonList;
//	auto createLesson = []() {
//		char lesson[20];
//		cout << "Please input the classes name, max lenght 20 characters and cannot have spaces. \n";
//		cin >> lesson;
//		return lesson;
//	};
//
//	cout << "Add classes to students curriculum." << endl;
//	char input;
//	do
//	{
//		lessonList.push_back(createLesson());
//		cout << "Do you want to add another lesson? y/n" << endl;
//		cin >> input;
//		cin.ignore();
//	} while (input == 'y' || input == 'Y');
//
//	return lessonList;
//}

void registerUser(Parent& parent)
{
	cout << "Set personal details for parent." << endl;
	createPersonalDetails(parent.personalDetails);
}

void registerUser(Teacher& teacher)
{
	cout << "Set personal details for teacher." << endl;
	createPersonalDetails(teacher.personalDetails);
}

void registerUser(Admin& admin) {
	cout << "Set personal details for admin." << endl;
	createPersonalDetails(admin.personalDetails);
}

void createPersonalDetails(Person& p)
{
	cout << "First name: ";
	cin >> p.firstName;

	cout << "Middle name: ";
	cin >> p.middleName;

	cout << "Last name: ";
	cin >> p.lastName;

	cout << "Gender: ";
	cin >> p.gender;

	cout << "Birth date in format mm/dd/yyyy: ";
	cin >> p.birthDate;

	cout << "Email address: ";
	cin >> p.emailAddress;

	cout << "Contact number: ";
	cin >> p.contactNumber;

	bool invalidUsername = false;
	do
	{
		char tempUsername[51];
		cout << "Username: ";
		cin >> tempUsername;
		if (isUsernameValid(tempUsername)) {
			strcpy_s(p.username, tempUsername);
			invalidUsername = false;
		}
		else {
			invalidUsername = true;
			cout << "Invalid username." << endl;
		}
	} while (invalidUsername);

	bool invalidPassword = false;
	do
	{
		char tempPassword[51];
		cout << "Password: ";
		cin >> tempPassword;
		if (isPasswordValid(tempPassword))
		{
			strcpy_s(p.password, tempPassword);
			invalidPassword = false;
		}
		else 
		{
			invalidPassword = true;
			cout << "Invalid password" << endl;
		}

	} while (invalidPassword);
	cin.ignore();
}

int setStudentId() {
	int tempId;
	bool invalidId = false;
	do
	{
		cout << "Set student id: ";
		cin >> tempId;
		// Check ID validity
	} while (invalidId);

	cin.ignore();
	return tempId;
}
bool isPasswordValid(string password) 
{
	for (char pass : password) // Foreach character in password check all invalid characters and if any are invalid return false.
	{ 
		for (char invalid : invalidPasswordChars)
		{
			if (pass == invalid)
				return false;
		}
	}
	return true;
}
bool isUsernameValid(string username) 
{
	auto toLower = [](string& s) { // Lambda function for converting a string or char[] to lowercase.
		transform(s.begin(), s.end(),
			s.begin(), ::tolower);
	};

	toLower(username);
	for (string x : usernames) {
		toLower(x);
		if (x == username)
			return false;
	}
	return true;
}