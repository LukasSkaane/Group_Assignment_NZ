#include <iostream>
#include <algorithm>

#include "Registration.h"
#include "StudentRecords.h"
#include "StorageHandling.h"

using namespace std;

enum Permissions { NONE, TEACHER_PERMS, ADMIN_PERMS };
enum MainMenuOptions { ADD = 1, EDIT, DELETE, UPDATE, SELECT_LECTURE, ALL_RECORDS, BACK };

template <class T>
void studentRecordsMenu(T&);
void displayMainMenu(const string, const int);
void displaySecondaryMenu();
int menuSelection(int min, int max);
int countStudentsInLecture(Lecture&);
int getLectureIndexByName(Lecture&, char[]);
bool isCharEmpty(char*);

bool getStudentByFirstName(Student&);
bool getStudentByUsername(Student&);
void registerNewUserThenSave(Student&);
void getStudentByIndex(Student&);

void selectStudent(Student&);

void addStudent(Student&, Lecture&);
void editStudent(Student&, Lecture&);
void deleteStudent(Student&, Lecture&);
void updateRecord(Student&, Lecture&);
int selectLecture(vector<Lecture>&);
void displayAllRecords(Lecture&);

int countStudents();

void studentRecords(Teacher& teacher) {
	studentRecordsMenu<Teacher>(teacher);
}
void studentRecords(Admin& admin) {
	studentRecordsMenu<Admin>(admin);
}

template <class T>
void studentRecordsMenu(T& user) {
	int selectionMenu,
		studentCount = 0,
		selectedLecture = -1;
	bool loopFlag = true;
	Student student;

	vector<Lecture> lectures;
	getLectures(lectures);

	if (!lectures.empty())
		do
		{
			system("CLS");
			if (selectedLecture == -1) {
				selectedLecture = selectLecture(lectures);
				system("CLS");
			}

			displayMainMenu(lectures[selectedLecture].lectureName, countStudentsInLecture(lectures[selectedLecture]));

			selectionMenu = menuSelection(ADD, BACK + 1);

			studentCount = countStudents();

			if (selectionMenu >= ADD && selectionMenu < SELECT_LECTURE) {
				system("CLS");

				if (studentCount != 0) {
					selectStudent(student);

					if (selectionMenu == ADD)
						addStudent(student, lectures[selectedLecture]);

					else if (selectionMenu == EDIT)
						editStudent(student, lectures[selectedLecture]);

					else if (selectionMenu == DELETE)
						deleteStudent(student, lectures[selectedLecture]);

					else if (selectionMenu == UPDATE)
						updateRecord(student, lectures[selectedLecture]);

					updateSavedLectures(lectures);
				}
				else {
					cout << "No students currently exist, do you want to register one? (y/n)" << endl;
					char input;
					cin >> input;
					if (tolower(input) == 'y') {
						registerNewUserThenSave(student);
					}
				}
			}
			else
			{
				if (selectionMenu == SELECT_LECTURE)
					selectedLecture = selectLecture(lectures);

				else if (selectionMenu == ALL_RECORDS)
					displayAllRecords(lectures[selectedLecture]);

				else if (selectionMenu == BACK)
					loopFlag = false;
			}
		} while (loopFlag);
	else {
		system("cls");
		cout << "No lectures exist, so none can be edited. Lectures can be created in the admin screen." << endl;
		system("pause");
	}
}

void selectStudent(Student& student) {
	enum StudentSelector { BY_NAME = 1, BY_USERNAME, REGISTER_NEW, BY_INDEX };
	int selectionMenu;
	bool selected = false;

	while (!selected) {

		displaySecondaryMenu();
		selectionMenu = menuSelection(BY_NAME, BY_INDEX);

		if (selectionMenu == BY_NAME) {
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
		else if (selectionMenu == BY_USERNAME) {
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
		else if (selectionMenu == REGISTER_NEW) {
			registerNewUserThenSave(student);
			selected = true;
		}
		else if (selectionMenu == BY_INDEX) {
			int selectionUser;

			vector<Student> students;
			getStudents(students);

			while (!selected) {
				cout << "Choose a student in the list: (fullname, username)" << endl;

				int count = 1;
				for (Student& x : students) {
					cout << count << ". " << x.personalDetails.firstName << " "
						<< x.personalDetails.middleName << " "
						<< x.personalDetails.lastName
						<< ", "
						<< x.personalDetails.username << endl;
					count++;
				}

				selectionUser = menuSelection(1, count);
				student = students[selectionUser - 1.];
				selected = true;
			}
		}
		else {
			cout << "Invalid input" << endl;
			selected = false;
		}
		system("CLS");
	}
}

void addStudent(Student& student, Lecture& lecture) {
	int studentAmount = countStudentsInLecture(lecture);
	bool studentExistsInLecture = false;
	char grade;
	char progression[51];

	for (int i = 0; i < studentAmount; i++) {
		if (strcmp(lecture.studentUsernames[i], student.personalDetails.username) == 0)
			studentExistsInLecture = true;
	}

	if (!studentExistsInLecture) {
		strcpy_s(lecture.studentUsernames[studentAmount], student.personalDetails.username);

		cout << "What is " << student.personalDetails.firstName << "'s grade?" << endl;
		cin >> grade;
		lecture.grades[studentAmount] = grade;
		cin.ignore();

		cout << "& how are they progressing? (Failed/Progressing/Achieved)" << endl;
		cin >> progression;
		strcpy_s(lecture.progression[studentAmount], progression);

		cout << "Added student " << student.personalDetails.username << " to lecture: " << lecture.lectureName << endl;
		cin.ignore();
	}
	else {
		cout << "This student is already in the selected lecture." << endl;
		system("pause");
	}
}
void editStudent(Student& student, Lecture& lecture) {
	int index = getLectureIndexByName(lecture, student.personalDetails.username);
	
	if (index != -1)
	{
		char grade;
		char progression[51];

		cout << "Student: " << lecture.studentUsernames[index] << endl
			<< "Grade: " << lecture.grades[index] << endl
			<< "Progression: " << lecture.progression[index] << endl << endl;

		cout << "New grade: ";
		cin >> grade;
		lecture.grades[index] = grade;

		cout << "New progression status: ";
		cin >> progression;
		strcpy_s(lecture.progression[index], progression);
	}
	else
		cout << "Student with username \'" << student.personalDetails.username << "\' is not in lecture " << lecture.lectureName << endl;

	system("pause");
}
void deleteStudent(Student& student, Lecture& lecture) {
	int arrSize = sizeof(lecture.studentUsernames) / sizeof(lecture.studentUsernames[0]);

	for (int i = 0; i < arrSize; i++) {
		if (strcmp(student.personalDetails.username, lecture.studentUsernames[i]) == 0) {
			for (int k = i; k < arrSize - 1; k++) {
				if (!isCharEmpty(lecture.studentUsernames[k + 1])) {
					strcpy_s(lecture.studentUsernames[k], lecture.studentUsernames[k + 1]);
					lecture.grades[k] = lecture.grades[k + 1];
					strcpy_s(lecture.progression[k], lecture.progression[k + 1]);
				}
				if (isCharEmpty(lecture.studentUsernames[k + 1])) {
					strcpy_s(lecture.studentUsernames[k], "");
					lecture.grades[k] = '\0';
					strcpy_s(lecture.progression[k], "");
					break;
				}
			}
		}
	}
}
void updateRecord(Student& student, Lecture& lecture) {
	cout << "Record updated." << endl;
	system("pause");
}
int selectLecture(vector<Lecture>& lectures) {
	lectures.clear();
	getLectures(lectures);

	int count = 0;
	int selection;

	cout << "Select lecture: " << endl;
	for (Lecture& x : lectures) {
		cout << count + 1 << ". " << x.lectureName << endl;
		count++;
	}

	selection = menuSelection(1, count);
	return selection - 1;
}
void displayAllRecords(Lecture& lecture) {
	int arrSize = sizeof(lecture.studentUsernames) / sizeof(lecture.studentUsernames[0]);
	int count = 1;

	vector<string> usernames, progression;
	vector<char> grades;

	for (int i = 0; i < arrSize; i++) {
		if (!isCharEmpty(lecture.studentUsernames[i])) {
			usernames.push_back(lecture.studentUsernames[i]);
			grades.push_back(lecture.grades[i]);
			progression.push_back(lecture.progression[i]);

			count++;
		}
	}

	count = 1;
	if (!usernames.empty()) {
		cout << "All Students in the lecture " << lecture.lectureName << "." << endl;
		for (string x : usernames) {
			cout << count << ". " << x << "\t" << grades[count - 1] << "\t" << progression[count - 1] << endl;
			count++;
		}
	}
	else
		cout << "No students saved in lecture " << lecture.lectureName << endl;


	system("pause");
}

int countStudents() {
	vector<Student> students;
	getStudents(students);

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
int countStudentsInLecture(Lecture& lecture) {
	int count = 0;
	for (string x : lecture.studentUsernames)
		if (!x.empty())
			count++;
	return count;
}
int getLectureIndexByName(Lecture& lecture, char username[]) {
	int arrayRowSize = sizeof lecture.studentUsernames / sizeof lecture.studentUsernames[0];

	for (int i = 0; i < arrayRowSize; i++) {
		if (strcmp(lecture.studentUsernames[i], username) == 0)
			return i;
	}
	return -1;
}

bool getStudentByFirstName(Student& student) {
	vector<Student> sameNameStudents;
	vector<Student> students;
	getStudents(students);
	int studentAmount = countStudents();

	char fName[51];
	cout << "Input first name: ";
	cin >> fName;

	for (int i = 0; i < studentAmount; i++) {
		if (strcmp(students[i].personalDetails.firstName, fName) == 0) {
			sameNameStudents.push_back(students[i]);
		}
	}

	if (sameNameStudents.size() > 1) {
		student = selectIfMultiple(students);
		return true;
	}
	else if (sameNameStudents.size() == 1) {
		student = sameNameStudents[0];
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
void registerNewUserThenSave(Student& student) {
	registerUser(student);
	saveToFile(student);
}

void displayMainMenu(const string lectureName, const int studentsInLecture) {
	cout << "Selected Lecture: " << lectureName << endl
		<< "Students in Lecture: " << studentsInLecture << endl
		<< "--------------------------------------" << endl;
	cout << "\t1. Add student" << endl;
	cout << "\t2. Edit student" << endl;
	cout << "\t3. Delete student" << endl;
	cout << "\t4. Update record" << endl;
	cout << "\t5. Select class" << endl;
	cout << "\t6. View all records" << endl << endl;
	cout << "\t7. Go back" << endl;
}
void displaySecondaryMenu() {
	cout << "Choose student by: " << endl;
	cout << "\t1. Search by Name. " << endl;
	cout << "\t2. Search by Username. " << endl;
	cout << "\t3. Register new Student. " << endl;
	cout << "\t4. Look through index." << endl;
}
int menuSelection(int min, int max) {
	int input;
	bool invalidInput = false;

	do {
		cin >> input;
		cin.clear();
		cin.ignore();

		if (input < min || input > max) {
			invalidInput = true;
			cout << "Invalid input" << endl;
		}
		else
			invalidInput = false;
	} while (invalidInput);
	return input;
}
bool isCharEmpty(char* c) {
	if (c != NULL && c[0] == '\0')
		return true;
	return false;
}