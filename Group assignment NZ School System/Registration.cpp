#include <iostream>
#include <string>
#include <iomanip>
#include <array>
#include "Registration.h"
#include "Structures.h"

using namespace std;

const array<char, 3> invalidPasswordChars = { '\\', '\'', '\"'}; 
// Disallowing back-slash (\), single-quote ('), double-quote (") because I believe incorrect handling would result in untraceable exception. (I'd rather not try to debug that)

void createPersonalDetails(Person&);
void createStudent(Student&);
void createParent(Parent&);
void createTeacher(Teacher&);
void createAdmin();

vector<string> addLessons();

void registration() 
{
	char input;
	vector<string> usernameList;
	// usernameList = getUsernames();
	
	cout << "Welcome to registration system.\n"
		<< "Please choose an option:\n"
		<< "1. Register Student\n"
		<< "2. Register Parent\n"
		<< "3. Register Teacher\n";	
	cin >> input;

	Student student;
	switch (input)
	{
	case '1':
	{
		createStudent(student);
		// saveStudent(student);
		break;
	}
	case '2': 
	{
		Parent parent;
		createParent(parent);
		// saveParent(parent);
		break;
	}
	case '3': 
	{
		Teacher teacher;
		createTeacher(teacher);
		// saveTeacher(teacher);
		break;
	}
	default:
		cout << "Invalid input" << endl;
		break;
	}
}

int setStudentId();
void createStudent(Student& student) 
{
	cout << "Set personal details for student." << endl;
	createPersonalDetails(student.personalDetails);
	student.studentId = setStudentId();
	student.classesList = addLessons();
	// setCaregiver(student.caregiverPrimary);
	// Ask to set secondary caregiver setCaregiver(student.caregiverSecondary);
}
vector<string> addLessons() 
{
	vector<string> lessonList;
	auto createLesson = []() {
		string lesson;
		cout << "Please input the classes name:\n";
		getline(cin, lesson);
		return lesson;
	};

	cout << "Add classes to students curriculum." << endl;
	char input;
	do
	{
		lessonList.push_back(createLesson());
		cout << "Do you want to add another lesson? y/n" << endl;
		cin >> input;
		cin.ignore();
	} while (input == 'y' || input == 'Y');

	return lessonList;
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


void createParent(Parent& parent)
{
	cout << "Set personal details for parent." << endl;
	createPersonalDetails(parent.personalDetails);
}


void createTeacher(Teacher& teacher)
{
	cout << "Set personal details for teacher." << endl;
	createPersonalDetails(teacher.personalDetails);

}

bool isPasswordValid(string);
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

	bool invalidUsername = false; // Only one of each username may exist.
	do
	{
		string tempUsername;
		cout << "Username: ";
		cin >> tempUsername;
		// Check username validity
		p.username = tempUsername;

	} while (invalidUsername);

	bool invalidPassword = false;
	do
	{
		string tempPassword;
		cout << "Password: ";
		cin >> tempPassword;
		if (isPasswordValid(tempPassword))
		{
			p.password = tempPassword;
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