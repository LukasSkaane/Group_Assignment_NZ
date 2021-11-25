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
void displayMainMenu(const string, const int);
void displaySecondaryMenu();
int menuSelection(int min, int max);
int countStudentsInLecture(Lecture&);
int getIndexForStudentInLecture(Lecture&, char[]);

bool getStudentByFirstName(Student&);
bool getStudentByUsername(Student&);
void registerNewStudent(Student&);
void getStudentByIndex(Student&);

void selectStudent(Student&);

void addStudent(Student&, Lecture&);
void editStudent(Student&, Lecture&);
void removeStudent(Student&, Lecture&);
void updateRecord(Student&, Lecture&);
int selectLecture(vector<Lecture>&);
void displayAllRecords(Lecture&);

void studentRecords(Teacher& teacher) {
	studentRecordsMenu<Teacher>(teacher, TEACHER_PERMS);
}
void studentRecords(Admin& admin) {
	studentRecordsMenu<Admin>(admin, ADMIN_PERMS);
}

void createTestLecture();

template <class T>
void studentRecordsMenu(T& user, int perms) {
	int selectionMenu;
	bool loopFlag = true;
	Student student;

	int selectedLecture = -1;
	vector<Lecture> lectures;
	getLectures(lectures);

	if (lectures.empty()) {
		Lecture testLecture;
		char name[51] = "CS101";
		strcpy_s(testLecture.lectureName, name);
		lectures.push_back(testLecture);
		updateSavedLecture(lectures);
	}

	do
	{
		system("CLS");
		if (selectedLecture == -1) {
			selectedLecture = selectLecture(lectures);
			system("CLS");
		}

		displayMainMenu(lectures[selectedLecture].lectureName, countStudentsInLecture(lectures[selectedLecture]));
		// createTestLecture();
		selectionMenu = menuSelection(ADD, BACK + 1);

		 if (selectionMenu == BACK + 1)
			createTestLecture();

		 else if (selectionMenu >= ADD && selectionMenu < SELECT_LECTURE) {
			system("CLS");

			selectStudent(student);

			if (selectionMenu == ADD)
				addStudent(student, lectures[selectedLecture]);

			else if (selectionMenu == EDIT)
				editStudent(student, lectures[selectedLecture]);

			else if (selectionMenu == DELETE)
				removeStudent(student, lectures[selectedLecture]);

			else if (selectionMenu == UPDATE)
				updateRecord(student, lectures[selectedLecture]);

			updateSavedLecture(lectures);
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
}

void selectStudent(Student& student) {
	enum StudentSelector { BY_NAME = 1, BY_USERNAME, REGISTER_NEW, BY_INDEX };
	int selectionMenu;
	bool selected = false;

	while (!selected) {
		displaySecondaryMenu();
		selectionMenu = menuSelection(BY_NAME, REGISTER_NEW);

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
			registerNewStudent(student);
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
	
	int index = countStudentsInLecture(lecture);
	char grade;
	char progression[51];
	
	strcpy_s(lecture.studentUsernames[index], student.personalDetails.username);

	cout << "What is " << student.personalDetails.firstName << "'s grade?" << endl;
	cin >> grade;
	lecture.grades[index] = grade;
	cin.ignore();

	cout << "& how are they progressing? (Failed/Progressing/Achieved)" << endl;
	cin >> progression;
	strcpy_s(lecture.progression[index], progression);

	cout << "Added student " << student.personalDetails.username << " to lecture: " << lecture.lectureName << endl;
	cin.ignore();
}
void editStudent(Student& student, Lecture& lecture) {
	int index = getIndexForStudentInLecture(lecture, student.personalDetails.username);
	
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
void removeStudent(Student& student, Lecture& lecture) {

}
void updateRecord(Student& student, Lecture& lecture) {

}
int selectLecture(vector<Lecture>& lectures) {
	lectures.clear();
	getLectures(lectures);

	int count = 0;
	int selection;

	if (!lectures.empty()) {
		cout << "Select lecture: " << endl;
		for (Lecture& x : lectures) {
			cout << count + 1 << ". " << x.lectureName << endl;
			count++;
		}

		selection = menuSelection(1, count);
		return selection - 1;
	}
	else {
		cout << "No lectures exist." << endl;
		system("pause");
		return 0;
	}
}
void displayAllRecords(Lecture& lecture){
	
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
int countStudentsInLecture(Lecture& lecture) {
	int arrayRowSize = sizeof lecture.studentUsernames / sizeof lecture.studentUsernames[0];
	int count = 0;
	bool empty = true;

	for (int i = 0; i < arrayRowSize; i++) {
		for (char x : lecture.studentUsernames[i]) {
			if (x != '0')
				empty = false;
		}
		if (empty)
			count++;
	}
	return count;
}
int getIndexForStudentInLecture(Lecture& lecture, char username[]) {
	int arrayRowSize = sizeof lecture.studentUsernames / sizeof lecture.studentUsernames[0];

	for (int i = 0; i < arrayRowSize; i++) {
		if (strcmp(lecture.studentUsernames[i], username))
			return i;
	}
	return -1;
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

	cout << "\t8. Create test lecture" << endl;
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
	char name[51];

	cout << "Name of Lecture: ";
	cin >> name;

	strcpy_s(lecture.lectureName, name);

	saveToFile(lecture);
	cout << "Lecture saved to file. " << endl;
	system("pause");
}