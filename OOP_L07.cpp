// OOP using C++ - Webinar 7 (01.09.2022)
// Homework - tasks 1, 2
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <memory>
using namespace std;


//Task 1------------------------------------------------------------------------------------------------------------------------------------

class Date {
public:
	Date(const int& _day, const int& _month, const int& _year) : day(_day), month(_month), year(_year) { cout << __FUNCTION__ << endl; }
	~Date() { cout << __FUNCTION__ << endl; }
	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }
private:
	int day;
	int month;
	int year;
};

ostream& operator<< (ostream& os, const Date& _date) {
	return os << _date.getDay() << "." << _date.getMonth() << "." << _date.getYear();
}

//End of task 1-----------------------------------------------------------------------------------------------------------------------------


//Task 2------------------------------------------------------------------------------------------------------------------------------------

Date maxDate(const unique_ptr<Date>& _date1, const unique_ptr<Date>& _date2) {
	if (_date1->getYear() > _date2->getYear()) return *_date1;
	else {
		if (_date1->getYear() < _date2->getYear()) return *_date2;
		else {
			if (_date1->getMonth() > _date2->getMonth()) return *_date1;
			else {
				if (_date1->getMonth() < _date2->getMonth()) return *_date2;
				else {
					if (_date1->getDay() > _date2->getDay()) return *_date1;
					else return *_date2;
				}
			}
		}
	}
}

void swapDate(unique_ptr<Date>& _date1, unique_ptr<Date>& _date2) {
	unique_ptr<Date> temp(new Date(*_date1));
	temp = move(_date1);
	_date1 = move(_date2);
	_date2 = move(temp);
}

//End of task 2-----------------------------------------------------------------------------------------------------------------------------


int main() {
	cout << "Tasks 1-------------------------------------------------------------------------------------------\n";
	unique_ptr<Date> today(new Date(4,9,2022)), date;
	cout << today->getDay() << " " << today->getMonth() << " " << today->getYear() << endl;
	cout << *today << endl;
	date = move(today); 
	cout << "auto_ptr<Date> today: " << today.get() << endl;
	cout << "auto_ptr<Date> date:  " << date.get() << endl;
	
	cout << endl;
	cout << "End of tasks 1------------------------------------------------------------------------------------\n\n";

	cout << "Tasks 2-------------------------------------------------------------------------------------------\n";
	unique_ptr<Date> date1(new Date (4,9,2022)), date2(new Date(5,9,2022));
	cout << "*date1: " << *date1 << "\n"
		 << "*date2: " << *date2 << endl;
	cout << "maxDate(date1, date2): " << maxDate(date1, date2) << endl;
	cout << "*date1: " << *date1 << "\n"
		 << "*date2: " << *date2 << endl;
	cout << "after swapDate(date1, date2):\n";
	swapDate(date1, date2);
	cout << "*date1: " << *date1 << "\n"
		 << "*date2: " << *date2 << endl;

	cout << endl;
	cout << "End of tasks 2------------------------------------------------------------------------------------\n\n";

	return 0;
}
