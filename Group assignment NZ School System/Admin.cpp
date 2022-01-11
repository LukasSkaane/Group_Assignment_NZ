#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype> 

#include "Admin.h"
#include "StudentRecords.h"
#include "StorageHandling.h"

using namespace std;

enum MainMenuOptions { NEW = 1, DELETE, REMOVE_ALL_STUDS, DISPLAY_LECTURE, DISPLAY_ALL_LECTURES, SELECT_LECTURE, BACK };

/// Add and remove Lectures, Remove students from lectures and other lecture related tasks. 
/// Display all students in a particular lecture or Display all students in all lectures.

void displayMenu();
int selectMenu(int, int);

void createNewLecture(vector<Lecture>&);
void removeLecture(vector<Lecture>&, int);
void removeAllStudentsFromLecture(Lecture&);
void displayLectureContents(Lecture&);
void displayAllLectureContents(vector<Lecture>&);

int selectLectureByName(vector<Lecture>&);

void adminMenu () {
	int selectionMenu;
	bool loopFlag = true;
	vector<Lecture> lectures;
	getLectures(lectures);

	int selectedLecture = -1;

	do
	{
		system("cls");
		displayMenu();

		selectionMenu = selectMenu(NEW, BACK);

		if (selectionMenu >= DELETE && selectionMenu <= DISPLAY_LECTURE) {
			if (selectedLecture == -1)
				cout << "No lecture selected. Cannot proceed." << endl;
			else {
				system("cls");
				if (selectionMenu == DELETE) {
					removeLecture(lectures, selectedLecture);
					selectedLecture = -1;
				}
				else if (selectionMenu == REMOVE_ALL_STUDS) {
					removeAllStudentsFromLecture(lectures[selectedLecture]);
					updateSavedLectures(lectures);
				}
				else if (selectionMenu == DISPLAY_LECTURE)
					displayLectureContents(lectures[selectedLecture]);
			}

			system("pause");
		}
		else
		{
			system("cls");

			if (selectionMenu == NEW)
				createNewLecture(lectures);

			else if (selectionMenu == DISPLAY_ALL_LECTURES)
				displayAllLectureContents(lectures);

			else if (selectionMenu == SELECT_LECTURE)
				selectedLecture = selectLectureByName(lectures);

			else if (selectionMenu == BACK)
				loopFlag = false;

			else
				cout << "Invalid Input.";
		}

	} while (loopFlag);
}

void createNewLecture(vector<Lecture>& lectures) {
	char lectureName[51];
	bool nameAvailable = true;
	bool loopFlag = false;

	do
	{
		cout << "Enter the name of the new lecture: ";
		cin >> lectureName;
		cin.ignore();

		for (Lecture& x : lectures) {
			if (strcmp(x.lectureName, lectureName) == 0)
				nameAvailable = false;
		}

		if (nameAvailable) {
			Lecture newLecture;
			strcpy_s(newLecture.lectureName, lectureName);

			lectures.push_back(newLecture);
			updateSavedLectures(lectures);
		}
		else {
			cout << "Name already exists, try again." << endl;
			system("pause");
		}
	} while (loopFlag);
}
void removeLecture(vector<Lecture>& lectures, int lectureIndex) {
	if (lectureIndex != -1) {
		cout << "Removing lecture with name: " << lectures[lectureIndex].lectureName << endl;
		lectures.erase(lectures.begin() + lectureIndex);
		updateSavedLectures(lectures);
	}
}
void removeAllStudentsFromLecture(Lecture& lecture) {
	char input;

	cout << "Are you sure you want to remove ALL students from " << lecture.lectureName << "? (y/n)" << endl;
	cin >> input;
	cin.ignore();

	if (tolower(input) == 'y') {
		cout << "Removing all students..." << endl;
		int studentsAmount = countStudentsInLecture(lecture);
		for (int i = 0; i < studentsAmount; i++) 
			strcpy_s(lecture.studentUsernames[i], "");
		
	}
}
void displayLectureContents(Lecture& lecture) {
	int studentAmount = countStudentsInLecture(lecture);

	cout << "--------------------------------------------------------" << endl
		<< "Lecture name: " << lecture.lectureName << endl;
	if (studentAmount == 0) 
		cout << "There are no students in this lecture..." << endl;
	else {
		cout << "Students in lecture: " << endl;
		for (int i = 0; i < studentAmount; i++) {
			cout << i + 1 << ". " << lecture.studentUsernames[i] << endl;
		}
	}
	cout << endl; 
}
void displayAllLectureContents(vector<Lecture>& lectures) {
	for (Lecture& x : lectures)
		displayLectureContents(x);
	system("pause");
}

int getLectureIndexByName(vector<Lecture>& lectures, char lectureName[]) {
	int count = 0;
	for (Lecture& x : lectures) {
		if (strcmp(x.lectureName, lectureName) == 0)
			return count;
		count++;
	}
	return -1;
}

int selectLectureByName(vector<Lecture>& lectures) {
	char lectureName[51];
	int index;

	cout << "Enter name of lecture: ";
	cin >> lectureName;
	cin.ignore();

	index = getLectureIndexByName(lectures, lectureName);
	
	if (index == -1) 
		cout << "No lectures exist by that name." << endl;
	
	else
		cout << "Lecture selected." << endl;

	system("pause");
	return index;
}


void displayMenu() {
	cout << "1. Create new lecture." << endl
		<< "2. Remove selected lecture." << endl
		<< "3. Remove all students from a lecture." << endl
		<< "4. Display all students in a lecture." << endl
		<< "5. Display all students in all lectures." << endl
		<< "6. Select lecture." << endl
		<< "7. Go back." << endl;
}
int selectMenu(int min, int max) {
	int input;
	bool invalidInput = false;

	do
	{
		cin >> input;
		cin.clear();
		cin.ignore();

		if (input < min && input > max) {
			invalidInput = true;
			cout << "Invalid input" << endl;
		}
		else
			invalidInput = false;
	} while (invalidInput);
	return input;
}