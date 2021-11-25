#ifndef STORAGEHANDLING_H
#define STORAGEHANDLING_H

#include "StorageHandling.h"
#include "Structures.h"

using namespace std;

void saveToFile(Student&);
void saveToFile(Parent&);
void saveToFile(Teacher&);
void saveToFile(Admin&);

void saveToFile(Lecture& lecture);
void updateSavedLecture(vector<Lecture>&);

void getUsernames(vector<string>&);
void getPasswords(vector<string>&);

void getStudents(vector<Student>&);
void getParents(vector<Parent>&);
void getTeachers(vector<Teacher>&);
void getAdmins(vector<Admin>&);

void getLectures(vector<Lecture>&);

#endif // !STORAGEHANDLING_H
