
#include <iostream>
#include "Structures.h"

#include "Introduction.h"

void add_parent(fstream& reg_stream);
void add_teacher(fstream& reg_stream);
void login_parent(fstream& log_stream);
void login_teacher(fstream& log_stream);


void main2()
{

	//fstream menu_stream;

	//int menu_choice = 0;

	//while (true) {
	//	cout << "\n\nEnter the choice from the menu:\n"
	//		<< "\n1: REGISTER AS PARENT. "
	//		<< "\n2: REGISTER AS TEACHER."
	//		<< "\n3: LOG-IN AS PARENT. "
	//		<< "\n4: LOG-IN AS TEACHER."
	//		<< "\n5: Quit the program."
	//		<< "\n\nYour choice is: ";
	//	cin >> menu_choice;
	//	cin.ignore();

	//	switch (menu_choice) {
	//	case 1:
	//		cout << "\nEnter the details of parent" << endl;
	//		add_parent(menu_stream);
	//		break;
	//	case 2:
	//		cout << "\nEnter the details of teecher" << endl;
	//		add_teacher(menu_stream);
	//		break;
	//	case 3:
	//		cout << "\nEnter your PARENT ID and PASSWORD" << endl;
	//		add_teacher(menu_stream);
	//		break;
	//	case 4:
	//		cout << "\nEnter your TEACHER ID and PASSWORD" << endl;
	//		add_teacher(menu_stream);
	//		break;
	//	case 5:
	//		"\n Quitting program";
	//		exit(0);
	//		break;
	//	default:
	//		cout << "Enter the correct options from the menu";
	//		break;
	//	}
	//}
}