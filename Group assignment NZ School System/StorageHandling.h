#ifndef STORAGEHANDLING_H
#define STORAGEHANDLING_H

#include "StorageHandling.h"
#include "Structures.h"

using namespace std;

void saveToFile(Student&);
void saveToFile(Parent&);
void saveToFile(Teacher&);
void saveToFile(Admin&);

void getUsernames(vector<string>&);

void getStudents(vector<Student>&);
void getParents(vector<Parent>&);
void getTeachers(vector<Teacher>&);
void getAdmins(vector<Admin>&);

#endif // !STORAGEHANDLING_H
