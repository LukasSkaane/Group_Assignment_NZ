#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <vector>

using namespace std;

struct Person {
	string
		firstName,
		middleName,
		lastName,
		gender,
		birthDate,
		emailAddress,
		contactNumber,
		username,
		password;
}; 

struct Student {
	int studentId = 0;
	vector<string> classesList; // Use push_front() to add to classes list.
	Person personalDetails;
	Person caregiverPrimary;
	Person caregiverSeconday;
};

struct Parent {
	vector<Student> children; // Parents children attending school.
	Person personalDetails;
};

struct Teacher {
	int classNumber = 0;
	string yearTaught;
	Person personalDetails;
};

struct Admin {

	Person personalDetails;
};

#endif // !STRUCTURES_H
