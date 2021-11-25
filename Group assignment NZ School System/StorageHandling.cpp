#include <iostream>
#include <fstream>
#include <locale>
#include <stdio.h>

#include "Structures.h"
#include "StorageHandling.h"

using namespace std;

const string FOLDER = "Saved/",
STUD_FILEPATH = FOLDER + "savedStudents.dat",
PARENT_FILEPATH = FOLDER + "savedParents.dat",
TEACHER_FILEPATH = FOLDER + "savedTeachers.dat",
ADMIN_FILEPATH = FOLDER + "savedAdmins.dat",
LECTURE_FILEPATH = FOLDER + "lectures.dat";

/// <Saving>
/// This section is used for saving different things to STUD_FILEPATH, PARENT_FILEPATH & TEACHER_FILEPATH;

template<class T>
void saveToBinaryFile(T, const string);
void clearFile(const string);

void saveToFile(Student& stud) {
	saveToBinaryFile(stud, STUD_FILEPATH);
}
void saveToFile(Parent& parent) {
	saveToBinaryFile(parent, PARENT_FILEPATH);
}
void saveToFile(Teacher& teacher) {
	saveToBinaryFile(teacher, TEACHER_FILEPATH);
}
void saveToFile(Admin& admin) {
	saveToBinaryFile(admin, TEACHER_FILEPATH);
}
void saveToFile(Lecture& lecture) {
	saveToBinaryFile(lecture, LECTURE_FILEPATH);
}
void updateSavedLecture(vector<Lecture>& lectures) {
	clearFile(LECTURE_FILEPATH);
	for (Lecture& x : lectures) {
		saveToFile(x);
	}
}

template<class T>
void saveToBinaryFile(T user, const string FILEPATH) {
	ofstream fileHandle;

	fileHandle.open(FILEPATH, ios::app | ios::binary);
	fileHandle.write(reinterpret_cast<char*>(&user), sizeof(user));
	fileHandle.close();
}

/// </Saving>

/// <Loading>
/// This section is used for loading different things from STUD_FILEPATH, PARENT_FILEPATH & TEACHER_FILEPATH;

template<class T>
void loadFromFilepath(vector<T>&, const string FILEPATH);
template<class T>
void extractUsernames(const vector<T>& user, vector<string>& usernames);
template<class T>
void extractPasswords(const vector<T>& user, vector<string>& passwords);

// These are here because you cannot call generic functions from another file, so an intermediary function is required.
void getStudents(vector<Student>& students) {
	loadFromFilepath<Student>(students, STUD_FILEPATH);
}
void getParents(vector<Parent>& parents) {
	loadFromFilepath<Parent>(parents, PARENT_FILEPATH);
}
void getTeachers(vector<Teacher>& teachers) {
	loadFromFilepath<Teacher>(teachers, TEACHER_FILEPATH);
}
void getAdmins(vector<Admin>& admins) { 
	loadFromFilepath<Admin>(admins, ADMIN_FILEPATH);
}

void getLectures(vector<Lecture>& lectures) {
	loadFromFilepath(lectures, LECTURE_FILEPATH);
}

void getUsernames(vector<string>& usernames) {
	vector<Student> students;
	vector<Parent> parents;
	vector<Teacher> teachers;
	vector<Admin> admins;

	loadFromFilepath<Student>(students, STUD_FILEPATH);
	loadFromFilepath<Parent>(parents, PARENT_FILEPATH);
	loadFromFilepath<Teacher>(teachers, TEACHER_FILEPATH);
	loadFromFilepath<Admin>(admins, ADMIN_FILEPATH);

	extractUsernames<Student>(students, usernames);
	extractUsernames<Parent>(parents, usernames);
	extractUsernames<Teacher>(teachers, usernames);
	extractUsernames<Admin>(admins, usernames);
}
void getPasswords(vector<string>& passwords) {
	vector<Student> students;
	vector<Parent> parents;
	vector<Teacher> teachers;
	vector<Admin> admins;

	loadFromFilepath<Student>(students, STUD_FILEPATH);
	loadFromFilepath<Parent>(parents, PARENT_FILEPATH);
	loadFromFilepath<Teacher>(teachers, TEACHER_FILEPATH);
	loadFromFilepath<Admin>(admins, ADMIN_FILEPATH);

	extractPasswords<Student>(students, passwords);
	extractPasswords<Parent>(parents, passwords);
	extractPasswords<Teacher>(teachers, passwords);
	extractPasswords<Admin>(admins, passwords);
}

template<class T>
void extractUsernames(const vector<T>& user, vector<string>& usernames) {
	for (const T& x : user) {
		usernames.push_back(x.personalDetails.username);
	}
}
template<class T>
void extractPasswords(const vector<T>& user, vector<string>& passwords) {
	for (const T& x : user) {
		passwords.push_back(x.personalDetails.password);
	}
}

template<class T>
void loadFromFilepath(vector<T>& users, const string FILEPATH) {
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

/// <Other>
void clearFile(const string FILEPATH) {
	ofstream fileHandle;

	fileHandle.open(FILEPATH); // Opening a file in non-append mode then closing it cleanly removes all contents inside a file.
	fileHandle.close();
}
/// </Other>