// OOP using C++ - Webinar 8 (05.09.2022)
// Homework 
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <exception>
#include <string>
using namespace std;


//Task 1------------------------------------------------------------------------------------------------------------------------------------

template<typename T1, typename T2>
auto Div(const T1& dividend, const T2& divisor) {
	try {
		const char* DivisionByZeroException = "DivisionByZero";
		if (divisor == 0) throw DivisionByZeroException;
		else return (double)dividend / (double)divisor;
	}
	catch(const char* e) {
		cerr << e << endl;
	}
}

//End of task 1-----------------------------------------------------------------------------------------------------------------------------


//Task 2------------------------------------------------------------------------------------------------------------------------------------

class Ex {
public:
	Ex(const double& _x) : x(_x) {}
	~Ex() {}
	double getx() const { return x; }
private:
	double x;
};

class Bar {
public:
	Bar() : y(0) {}
	~Bar() {}
	void set(const double& a) { 
		try {
			if ((y + a) > 100) throw Ex(a * y);
			else y = a;
		}
		catch (Ex e) {
			cerr << "Exception: Ex(" << a << "*" << y << ") = " << e.getx() << endl;
		}
	}
private:
	double y;
};

//End of task 2-----------------------------------------------------------------------------------------------------------------------------


//Task 3------------------------------------------------------------------------------------------------------------------------------------

class OffTheField {
public:
	OffTheField(const int& _current_x, const int& _current_y, const int& _next_x, const int& _next_y) 
		: current_x(_current_x), current_y(_current_y), next_x(_next_x), next_y(_next_y) {}
	~OffTheField() {}
	void print() const {
		cout << "OffTheField(current_x: " << current_x << ", current_y: " << current_y << ", next_x: " << next_x << ", next_y: " << next_y << ")";
	}
private:
	int current_x;
	int current_y;
	int next_x;
	int next_y;
};

class IllegalCommand {
public:
	IllegalCommand(const int& _current_x, const int& _current_y, const int& _move_x, const int& _move_y) 
		: current_x(_current_x), current_y(_current_y), move_x(_move_x), move_y(_move_y) {}
	~IllegalCommand() {}
	void print() const {
		cout << "IllegalCommand(current_x: " << current_x << ", current_y: " << current_y << ", move_x: " << move_x << ", move_y: " << move_y << ")";
	}
private:
	int current_x;
	int current_y;
	int move_x;
	int move_y;
};

class Robot {
public:		
	Robot() : current_x(1), current_y(1) {}
	Robot(const int& _start_x, const int& _start_y) {
		if (_start_x >= 1 && _start_x <= 10 && _start_y >= 1 && _start_y <= 10) {
			current_x = _start_x;
			current_y = _start_y;
		}
		else throw OffTheField(0, 0, _start_x, _start_y);
	}
	~Robot() {}
	void printPosition() const { cout << "Robot position(X = " << current_x << ", Y = " << current_y << ")"; }
	void MoveToNearField(const int& move_x, const int& move_y) {
		if (abs(move_x) > 1 || abs(move_y) > 1) throw IllegalCommand(current_x, current_y, move_x, move_y);
		else {
			if ((current_x + move_x) < 1 || (current_x + move_x) > 10 || (current_y + move_y) < 1 || (current_y + move_y) > 10)
				throw OffTheField(current_x, current_y, current_x + move_x, current_y + move_y);
			else {
				current_x += move_x;
				current_y += move_y;
			}
		}
	};
private:
	int current_x;
	int current_y;
};


//End of task 3-----------------------------------------------------------------------------------------------------------------------------



int main() {

	cout << "Tasks 1-------------------------------------------------------------------------------------------\n";
	try {
		cout << "Div(7, 2) = " << Div(7, 2) << endl;
		cout << "Div(10.4, 2.6) = " << Div(10.4, 2.6) << endl;
		cout << "Div(6, 0) = " << Div(6, 0) << endl;
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown exception" << endl;
		return 2;
	}

	cout << endl;
	cout << "End of tasks 1------------------------------------------------------------------------------------\n\n";

	cout << "Tasks 2-------------------------------------------------------------------------------------------\n";
	try {
		Bar b;
		int n{1};
		while (n != 0) {
			while (true) {
				cout << "Please, enter an integer value for n: ";
				string current_input;
				getline(cin, current_input);
				int input_size = current_input.size();
				if (input_size == 0) cerr << "Incorrect input. Please, try again\n";
				else {
					int nan_counter{ 0 };
					for (int i = 0; i < input_size; i++) {
						if (i == 0) {
							if (!isdigit(current_input[i]) && current_input[i] != '-' && current_input[i] != '+') {
								nan_counter++;
								break;
							}
						}
						else {
							if (!isdigit(current_input[i])) {
								nan_counter++;
								break;
							}
						}
					}
					if (nan_counter > 0) cerr << "Incorrect input. Please, try again\n";
					else {
						n = stoi(current_input);
						break;
					}
				}
			}
			b.set(n);
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown exception" << endl;
		return 2;
	}

	cout << endl;
	cout << "End of tasks 2------------------------------------------------------------------------------------\n\n";


	cout << "Tasks 3-------------------------------------------------------------------------------------------\n";
	try {
		try {
			cout << "Robot r1:\n";
			Robot r1(3, 7);
			r1.printPosition();
			cout << endl;
			r1.MoveToNearField(-1, 1);
			r1.printPosition();
			cout << endl;
			r1.MoveToNearField(-1, 1);
			r1.printPosition();
			cout << endl;
			r1.MoveToNearField(-2, 1);
			r1.printPosition();
			cout << endl;
		}
		catch (OffTheField &e) {
			cerr << "Robot::Exception::";
			e.print();
			cerr << endl;
		}
		catch (IllegalCommand &e) {
			cerr << "Robot::Exception::";
			e.print();
			cerr << endl;
		}
		catch (...) {
			throw;
		}

		cout << endl;

		try {
			cout << "Robot r2:\n";
			Robot r2(-3,9);
			r2.printPosition();
			cout << endl;
			
			cout << endl;
		}
		catch (OffTheField &e) {
			cerr << "Robot::Exception::";
			e.print();
			cerr << endl;
		}
		catch (IllegalCommand &e) {
			cerr << "Robot::Exception::";
			e.print();
			cerr << endl;
		}
		catch (...) {
			throw;
		}

		cout << endl;

		try {
			cout << "Robot r3:\n";
			Robot r3(8, 1);
			r3.printPosition();
			cout << endl;
			r3.MoveToNearField(1, 0);
			r3.printPosition();
			cout << endl;
			r3.MoveToNearField(1, 1);
			r3.printPosition();
			cout << endl;
			r3.MoveToNearField(1, 1);
			r3.printPosition();
			cout << endl;

			cout << endl;
		}
		catch (OffTheField &e) {
			cerr << "Robot::Exception::";
			e.print();
			cerr << endl;
		}
		catch (IllegalCommand &e) {
			cerr << "Robot::Exception::";
			e.print();
			cerr << endl;
		}
		catch (...) {
			throw;
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown exception" << endl;
		return 2;
	}
	
	cout << endl;
	cout << "End of tasks 3------------------------------------------------------------------------------------\n\n";

	return 0;
}
