#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

struct Person {
	char
		firstName[51],
		middleName[51],
		lastName[51],
		gender[16],
		birthDate[51],
		emailAddress[26],
		contactNumber[51],
		username[51],
		password[51];
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
	char yearTaught[51];
	Person personalDetails;
};

struct Admin {

	Person personalDetails;
};

#endif // !STRUCTURES_H