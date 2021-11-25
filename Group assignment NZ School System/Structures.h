#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;
const int maxStudents = 20;

struct Person {
	char
		firstName[51] = { 0 },
		middleName[51] = { 0 },
		lastName[51] = { 0 },
		gender[16] = { 0 },
		birthDate[51] = { 0 },
		emailAddress[26] = { 0 },
		contactNumber[51] = { 0 },
		username[51] = { 0 },
		password[51] = { 0 };
};

struct Student {
	int studentId = 0;
	Person personalDetails;
	Person caregiverPrimary;
	Person caregiverSeconday;
};

struct Parent {
	Person personalDetails;
};

struct Teacher {
	int classNumber = 0;
	char yearTaught[51] = { 0 };
	Person personalDetails;
};

struct Admin {
	Person personalDetails;
};

struct Lecture {
	char lectureName[51] = { 0 },
		studentUsernames[maxStudents][51] = { 0 },
		grades[maxStudents] = { 0 },
		progression[maxStudents][51] = { 0 }; // Achieved, Progressing, Need Help.
};



#endif // !STRUCTURES_H