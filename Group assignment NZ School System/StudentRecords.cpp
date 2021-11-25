#include <iostream>
#include <algorithm>

#include "Structures.h"
#include "Registration.h"
#include "StudentRecords.h"
#include "StorageHandling.h"

using namespace std;

enum Permissions { NONE, TEACHER_PERMS, ADMIN_PERMS };
enum MainMenuOptions { ADD = 1, EDIT, DELETE, UPDATE, SELECT_LECTURE, ALL_RECORDS, BACK };

template <class T>
void studentRecordsMenu(T&, int);
void displayMainMenu();
void displaySecondaryMenu();
int menuSelection(int min, int max);

bool getStudentByFirstName(Student&);
bool getStudentByUsername(Student&);
void registerNewStudent(Student&);

void selectStudent(Student&);

void addStudent(Student&, Lecture&);
void editStudent(Student&, Lecture&);
void deleteStudent(Student&, Lecture&);
void updateRecord(Student&, Lecture&);
void selectLecture(Lecture&);
void displayAllRecords();

void studentRecords(Teacher& teacher) {
	studentRecordsMenu<Teacher>(teacher, TEACHER_PERMS);
}
void studentRecords(Admin& admin) {
	studentRecordsMenu<Admin>(admin, ADMIN_PERMS);
}

void createTestLecture();


template <class T>
void studentRecordsMenu(T& user, int perms) {
	int selection;
	bool loopFlag = true;
	Student student;
	Lecture selectedLecture;

	do
	{
		system("CLS");
		selectLecture(selectedLecture);
		system("CLS");

		displayMainMenu();
		// createTestLecture();
		selection = menuSelection(ADD, BACK);

		if (selection >= ADD && selection < SELECT_LECTURE) {
			system("CLS");

			selectStudent(student);

			if (selection == ADD)
				addStudent(student, selectedLecture);

			else if (selection == EDIT)
				editStudent(student, selectedLecture);

			else if (selection == DELETE)
				deleteStudent(student, selectedLecture);

			else if (selection == UPDATE)
				updateRecord(student, selectedLecture);
		}
		else
		{
			if (selection == SELECT_LECTURE)
				selectLecture(selectedLecture);

			else if (selection == ALL_RECORDS)
			displayAllRecords();

			else if (selection == BACK)
			loopFlag = false;
		}
	} while (loopFlag);
}

void selectStudent(Student& student) {
	enum StudentSelector { BY_NAME = 1, BY_USERNAME, REGISTER_NEW };
	int selection;
	bool selected = false;

	displaySecondaryMenu();
	selection = menuSelection(BY_NAME, REGISTER_NEW);

	if (selection == BY_NAME) {
		while (!selected) {
			if (getStudentByFirstName(student))
				selected = true;
			else {
				cout << "No students with that first name exist." << endl;
				cout << "Do you want to try again? (y/n)" << endl;
				char input;
				cin >> input;
				if (tolower(input) == 'n')
					break;
				else 
					continue;
			}
		}
	}
	else if (selection == BY_USERNAME) {		
		while (!selected) {
			if (getStudentByUsername(student))
				selected = true;
			else {
				cout << "No students with that username exist." << endl;
				cout << "Do you want to try again? (y/n)" << endl;
				char input;
				cin >> input;
				if (tolower(input) == 'n')
					break;
				else
					continue;
			}
		}
	}
	else if (selection == REGISTER_NEW) {
		registerNewStudent(student);
		selected = true;
	}
	else {
		cout << "Invalid input" << endl;
		selected = false;
	}
}

void addStudent(Student& student, Lecture& lecture) {
	
}
void editStudent(Student& student, Lecture& lecture) {

}
void deleteStudent(Student& student, Lecture& lecture) {

}
void updateRecord(Student& student, Lecture& lecture) {

}
void selectLecture(Lecture& lecture) {
	vector<Lecture> lectures;
	getLectures(lectures);

	int count = 1;
	int selection;

	if (!lectures.empty()) {
		cout << "Select lecture: " << endl;
		for (Lecture& x : lectures) {
			cout << count << ". " << x.lectureName << endl;
			count++;
		}

		selection = menuSelection(1, count);
		lecture = lectures[selection - 1];
	}
	else {
		cout << "No lectures exist." << endl;
		system("pause");
	}
}
void displayAllRecords(){
	
}

int countStudents(vector<Student>& students) {
	int count = 0;
	for (Student& x : students)
		count++;

	return count;
}
Student selectIfMultiple(vector<Student>& students) {
	int count = 1;
	int selection;

	for (Student& x : students) {
		cout << count << ". Name: " << x.personalDetails.firstName << " "
			<< x.personalDetails.middleName << " "
			<< x.personalDetails.lastName << " | Username: "
			<< x.personalDetails.username;
		cout << endl;
		count++;
	} // Outputs: '1. Name: firstname middlename lastname | Username: username';

	selection = menuSelection(1, count);

	return students[selection - 1.0];
}

bool getStudentByFirstName(Student& student) {
	vector<Student> students;
	getStudents(students);

	string fName;
	cout << "Input first name: ";
	cin >> fName;

	for (int i = 0; i < countStudents(students); i++) {
		if (students[i].personalDetails.firstName != fName) {
			students.erase(students.begin() + i);
			i--;
		}
	}

	if (countStudents(students) > 1) {
		student = selectIfMultiple(students);
		return true;
	}
	else if (countStudents(students) == 1) {
		student = students[0];
		return true;
	}
	else
		return false;
}
bool getStudentByUsername(Student& student) {
	auto toLower = [](string& s) { // Lambda function for converting a string or char[] to lowercase.
		transform(s.begin(), s.end(),
			s.begin(), ::tolower);
	};

	vector<Student> students;
	getStudents(students);

	string username, tempUsername;
	cout << "Input username: ";
	cin >> username;

	for (Student& x : students) {
		tempUsername = x.personalDetails.username;
		toLower(tempUsername);
		toLower(username);
		if (tempUsername == username) {
			student = x;
			return true;
		}
	}
	return false;
}
void registerNewStudent(Student& student) {
	registerUser(student);
}

void displayMainMenu() {
	cout << "1. Add student" << endl;
	cout << "2. Edit student" << endl;
	cout << "3. Delete student" << endl;
	cout << "4. Update record" << endl;
	cout << "5. Select class" << endl;
	cout << "6. View all records" << endl << endl;
	cout << "7. Go back" << endl;
}
void displaySecondaryMenu() {
	cout << "Choose student by: " << endl;
	cout << "1. Search by Name. " << endl;
	cout << "2. Search by username. " << endl;
	cout << "3. Register new student. " << endl;
	cout << "4. Go Back. " << endl;
}
int menuSelection(int min, int max) {
	int input;
	bool invalidInput = false;

	do
	{
		cin >> input;
		if (input < min && input > max) {
			invalidInput = true;
			cout << "Invalid input" << endl;
		}
		else
			invalidInput = false;
		} while (invalidInput);
	return input;
}

void createTestLecture() {
	Lecture lecture;
	lecture.lectureName[0] =  'C';
	lecture.lectureName[1] = 'S';
	lecture.lectureName[2] = '1';
	lecture.lectureName[3] = '0';
	lecture.lectureName[4] = '3';
	saveToFile(lecture);
	cout << "Lecture saved to file. " << endl;
	system("pause");
}