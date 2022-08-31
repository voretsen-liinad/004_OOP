// OOP using C++ - Webinar 6 (29.08.2022)
// Homework - tasks 1, 2
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <string>
using namespace std;


//Task 1------------------------------------------------------------------------------------------------------------------------------------

int Read_int() {
	while (true) {
		cout << "Enter an integer number: ";
		string s;
		getline(cin, s);
		if (s.size() == 0) cerr << "Error: input is not an integer number\n"; 
		else {
			int limit = s.size() - 1;
			int counter{ 0 };
			for (int i = 0; i <= limit; i++) {
				if (i == 0) {
					if (!isdigit(s[i]) && s[i] != '-' && s[i] != '+') counter++;
				}
				else if (!isdigit(s[i])) counter++;
				if (counter > 0) break;
			}
			if (counter > 0) cerr << "Error: input is not an integer number\n";
			else return stoi(s);
		}
	}
}

//End of task 1-----------------------------------------------------------------------------------------------------------------------------


//Task 2------------------------------------------------------------------------------------------------------------------------------------

ostream& endll(ostream& os) {
	return os << "\n" << endl;
}

//End of task 1-----------------------------------------------------------------------------------------------------------------------------


int main() {

	cout << "Tasks 1 and 2-------------------------------------------------------------------------------------\n";
	int n = Read_int();
	cout << "You have entered an integer number: " << n << endll;
	cout << "End of tasks 1 and 2------------------------------------------------------------------------------\n\n";

	return 0;
}
