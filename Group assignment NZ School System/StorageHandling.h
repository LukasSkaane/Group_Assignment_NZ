#ifndef STORAGEHANDLING_H
#define STORAGEHANDLING_H

#include "StorageHandling.h"
#include "Structures.h"

using namespace std;

void saveToFile(Student&);
void saveToFile(Parent&);
void saveToFile(Teacher&);

void getUsernames(vector<string>&);

void getStudents(vector<Student>& students);
void getParents(vector<Parent>& parents);
void getTeachers(vector<Teacher>& teachers);

#endif // !STORAGEHANDLING_H
