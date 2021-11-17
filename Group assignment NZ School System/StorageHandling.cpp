#include <istream>
#include <ostream>
#include <locale>

#include "Structures.h"
#include "StorageHandling.h"

using namespace std;

const string FOLDER = "Saved/",
STUD_FILEPATH = FOLDER + "savedStudents.dat",
PARENT_FILEPATH = FOLDER + "savedParents.dat",
TEACHER_FILEPATH = FOLDER + "savedTeachers.dat";

/// <Saving>
/// This section is used for saving different things to STUD_FILEPATH, PARENT_FILEPATH & TEACHER_FILEPATH;

template<class T>
void saveToBinaryFile(T, const string);

void saveToFile(Student& stud) {
	saveToBinaryFile(stud, STUD_FILEPATH);
}

void saveToFile(Parent& parent) {
	saveToBinaryFile(parent, PARENT_FILEPATH);
}

void saveToFile(Teacher& teacher) {
	saveToBinaryFile(teacher, TEACHER_FILEPATH);
}

template<class T>
void saveToBinaryFile(T user, const string FILEPATH) {
	ofstream fileHandle;

	fileHandle.open(FILEPATH, ios::app | ios::binary);
	fileHandle.write(reinterpret_cast<char*>(&user), sizeof(user));
	fileHandle.close();
	cout << "Saved to file." << endl;
}

/// </Saving>

/// <Loading>
/// This section is used for loading different things from STUD_FILEPATH, PARENT_FILEPATH & TEACHER_FILEPATH;

template<class T>
void getUsersFromFilepath(vector<T>&, const string FILEPATH);
template<class T>
void extractUsernames(const vector<T>& user, vector<string>& usernames);

void getStudents(vector<Student>& students) {
	getUsersFromFilepath<Student>(students, STUD_FILEPATH);
}
void getParents(vector<Parent>& parents) {
	getUsersFromFilepath<Parent>(parents, PARENT_FILEPATH);
}
void getTeachers(vector<Teacher>& teachers) {
	getUsersFromFilepath<Teacher>(teachers, TEACHER_FILEPATH);
}

void getUsernames(vector<string>& usernames) {
	vector<Student> students;
	vector<Parent> parents;
	vector<Teacher> teachers;

	getUsersFromFilepath<Student>(students, STUD_FILEPATH);
	getUsersFromFilepath<Parent>(parents, PARENT_FILEPATH);
	getUsersFromFilepath<Teacher>(teachers, TEACHER_FILEPATH);

	extractUsernames<Student>(students, usernames);
	extractUsernames<Parent>(parents, usernames);
	extractUsernames<Teacher>(teachers, usernames);
}

template<class T>
void extractUsernames(const vector<T>& user, vector<string>& usernames) {
	for (const T& x : user) {
		usernames.push_back(x.personalDetails.username);
	}
}

template<class T>
void getUsersFromFilepath(vector<T>& users, const string FILEPATH) {
	ifstream inHandle;

	T buffer;
	inHandle.open(FILEPATH, ios::binary);
	if (inHandle) {
		inHandle.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
		while (!inHandle.eof()) {
			users.push_back(buffer);
			inHandle.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
		}
	}
	inHandle.close();
}

/// </Loading>