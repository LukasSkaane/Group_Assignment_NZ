#include "Login.h"
#include "Structures.h"
#include "StorageHandling.h"
#include "Menu.h"

using namespace std;

template <class T>
bool logUserIn(T& user, vector<T>&);

bool login(Student& student) {
	vector<Student> students;
	getStudents(students);
	return logUserIn(student, students);
}
bool login(Parent& parent) {
	vector<Parent> parents;
	getParents(parents);
	return logUserIn(parent, parents);
}
bool login(Teacher& teacher) {
	vector<Teacher> teachers;
	getTeachers(teachers);
	return logUserIn(teacher, teachers);
}
bool login(Admin& admin) {
	vector<Admin> admins;
	getAdmins(admins);
	return logUserIn(admin, admins);
}

template <class T>
bool logUserIn(T& user, vector<T>& storedUsers) {
	system("cls");
	char username[51], password[51];
	int index = -1; // If a matching username is found, its index will get stored within this variable.
	bool successfulLogIn = false;

	cout << "Username?" << endl;
	cin >> username;

	int count = 0;
	for (T& x : storedUsers) {
		if (strcmp(x.personalDetails.username, username) == 0) {
			index = count;
			break;
		}
		count++;
	}

	if (index != -1) {
		for (int i = 3; i > 0; i--) {
			cout << "Password? You have " << i << " tries left." << endl;
			cin >> password;

			if (strcmp(storedUsers[index].personalDetails.password, password) == 0) {
				cout << "Successfully logged in." << endl;
				user = storedUsers[index];
				successfulLogIn = true;
				break;
			}
			else if (i == 1)
				cout << "Failed log in, going back to main menu." << endl;
		}
		system("pause");
	}
	else {
		cout << "No user with that username found." << endl;
		system("pause");
	}
	return successfulLogIn;
}