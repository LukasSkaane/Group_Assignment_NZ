#include <fstream>
#include <string>
#include <iostream>

using namespace std;

bool saveStudentToFile();
bool saveParentToFile();
bool loginAsTeacher()
{
	ifstream read;
	
	string username, password, un, pw;
	int menu_option;
	do {
		cout << "LOGIN PAGE - *******************";
		cout << "\n 1. LOG-IN AS STUDENT";
		cout << "\n 2. LOG-IN AS PARENT";
		cout << "\n 3. LOG-IN AS TEACHER";
		cout << "\n 4. EXIT";

		cout << "\n\n Enter your option: ";
		cin >> menu_option;

		switch (menu_option)
		{
		case 1:
			cout << "LOGIN AS STUDENT";
			cout << "****************";
			cout << "Enter UserName :   "; cin >> username;
			cout << "Enter PassWord :   "; cin >> password;

			
			read.open("data\\" + username + ".txt");
			getline(read, un);
			getline(read, pw);

			if (un == username && pw == password)
			{
				return true;
			}
			else
			{
				return false;
			}

			break;
		case 2:
			cout << " LOGIN AS PARENT";
			cout << "****************";
			cout << "Enter UserName :   ";
			cin >> username;
			cout << "Enter PassWord :   ";
			cin >> password;

			
			read.open("data\\" + username + ".txt");
			getline(read, un);
			getline(read, pw);

			if (un == username && pw == password)
			{
				return true;
			}
			else
			{
				return false;
			}
			
			break;
		case 3:
			cout << " LOGIN AS TEACHER";
			cout << "****************";
			cout << "Enter UserName :   "; cin >> username;
			cout << "Enter PassWord :   "; cin >> password;

			
			read.open("data\\" + username + ".txt");
			getline(read, un);
			getline(read, pw);

			if (un == username && pw == password)
			{
				return true;
			}
			else
			{
				return false;
			}


			break;
		case 4:
			exit(0);
			break;

		default:
			cout << "Sorry incorrect option entered in menu";
			break;
		
		

		}
	}while (true);
	system("CLS");

	
}