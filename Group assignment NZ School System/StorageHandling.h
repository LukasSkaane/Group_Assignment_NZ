#ifndef STORAGEHANDLING_H
#define STORAGEHANDLING_H

#include "StorageHandling.h"
#include "Structures.h"

using namespace std;

void saveToFile(Student&);
void saveToFile(Parent&);
void saveToFile(Teacher&);

void getUsernames(vector<string>&);

#endif // !STORAGEHANDLING_H
