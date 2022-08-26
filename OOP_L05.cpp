// OOP using C++ - Webinar 5 (25.08.2022)
// Homework - tasks 1, 2, 3
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <string>

using namespace std;


//Task 1------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
class Pair1 {
public:
	Pair1(const T& _a, const T& _b) : a(_a), b(_b) {}
	~Pair1() {}
	T first() const { return a; } 
	T second() const { return b; } 
private:
	T a;
	T b;
};

//End of task 1-----------------------------------------------------------------------------------------------------------------------------


//Task 2------------------------------------------------------------------------------------------------------------------------------------

template<typename T1, typename T2>
class Pair {
public:
	Pair(const T1& _a, const T2& _b) : a(_a), b(_b) {}
	~Pair() {}
	T1 first() const { return a; }
	T2 second() const { return b; }
private:
	T1 a = 5;
	T2 b = 4;
};

//End of task 2-----------------------------------------------------------------------------------------------------------------------------


//Task 3------------------------------------------------------------------------------------------------------------------------------------

template<typename T2>
class StringValuePair : public Pair<string, T2> {
public:
	StringValuePair(const string& _a, const T2& _b) : Pair<string, T2>(_a, _b) {}
	~StringValuePair() {}
};

//End of task 3-----------------------------------------------------------------------------------------------------------------------------


int main() {

	cout << "Task 1-------------------------------------------------------------------------------------\n";
	Pair1<int> p1(6, 9);
	cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2(3.4, 7.8);
	cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
	cout << endl;
	cout << "End of task 1------------------------------------------------------------------------------\n\n";


	cout << "Task 2-------------------------------------------------------------------------------------\n";	
	Pair<int, double> P1(6, 7.8);
	cout << "Pair: " << P1.first() << ' ' << P1.second() << '\n';

	const Pair<double, int> P2(3.4, 5);
	cout << "Pair: " << P2.first() << ' ' << P2.second() << '\n';
	cout << endl;
	cout << "End of task 2------------------------------------------------------------------------------\n\n";


	cout << "Task 3-------------------------------------------------------------------------------------\n";
	StringValuePair<int> svp("Amazing", 7);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
	cout << endl;
	cout << "End of task 3------------------------------------------------------------------------------\n\n";

	return 0;
}
