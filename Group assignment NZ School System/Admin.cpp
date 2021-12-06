#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype> 

using namespace std;

const int NAME_SIZE = 50, NUM_SIZE = 20, ADDRESS_SIZE = 30;
struct Student {
	char first_name[NAME_SIZE];
	char middle_name[NAME_SIZE];
	char last_name[NAME_SIZE];
	char gender[NUM_SIZE];
	char birth_date[ADDRESS_SIZE];
	char email_address[ADDRESS_SIZE];
	char phone_number[ADDRESS_SIZE];
};

void search_student_by_name(fstream& student_stream);


void search_student_by_name(fstream& student_stream)
{
	Student s;
	char name[NAME_SIZE];
	bool flag = false;

	// Using the filestream variable, we open the file 'student.dat' for reading -> ios::in
   // And indicate that this is a binary file -> ios::binary
	student_stream.open("student.dat", ios::in | ios::binary);
	string student_data;

	//If the file does not exist or if there is an error opening the file, show an error message
	if (!student_stream)
	{
		cout << "File does not exist or there is a problem opening the file";
	}
	else //if file exists and no problems opening it, then read the binary data
	{
		cout << "Enter the name of the student whose details you want to see: ";
		cin.getline(name, NAME_SIZE);
		cout << "\n";

		student_stream.read(reinterpret_cast<char*>(&s), sizeof(s));
		while (!student_stream.eof()) //keep running this file loop until the end of file (eof) is reached
		{
			if (strcmp(name, s.first_name) == 0) // if the name I entered is the same as the
			// student name in the current student record, then I display the details of that student
			{
				cout << "First Name: " << s.first_name << endl;
				cout << "Middle Name: " << s.middle_name << endl;
				cout << "Last Name: " << s.last_name << endl;
				cout << "Gender: " << s.gender << endl;
				cout << "Birth Date: " << s.birth_date << endl;
				cout << "Email Address: " << s.email_address << endl;
				cout << "Phone Number: " << s.phone_number << endl;
				cout << "\n";
				flag = true; //Update flag is true
				cout << "The above are details of the student with name: " << name;
			}
			student_stream.read(reinterpret_cast<char*>(&s), sizeof(s));
		}

		if (flag == false)
		{
			cout << "\n No records for the student found\n";
		}

	}
	student_stream.close(); //Please ensure you close the file after reading all data

}