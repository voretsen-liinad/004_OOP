// OOP using C++ - Webinar 1 (11.08.2022)
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <cstdint>

using namespace std;

//Task 1-----------------------------------------------------------------------

class Power {
public:
	Power() : Base(0), Exp(1) {}
	
	void set(const double& _Base, const double& _Exp) {
		Base = _Base;
		Exp = _Exp;
	}
	
	void calculate() {
		cout << Base << "^" << Exp << " = " << pow(Base, Exp) << endl;
	}

private:
	double Base;
	double Exp;
};

//End of task 1----------------------------------------------------------------


//Task 2-----------------------------------------------------------------------

class RGBA {
public:
	RGBA(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255) : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {}
	
	void print() {
		cout << "m_red = " << (int)m_red << ", m_green = " << (int)m_green << ", m_blue = " << (int)m_blue << ", m_alpha = " << (int)m_alpha << endl;
	}

private:
	uint8_t m_red;
	uint8_t m_green;
	uint8_t m_blue;
	uint8_t m_alpha;
};

//End of task 2----------------------------------------------------------------


//Task 3-----------------------------------------------------------------------

class Stack {
public:
	Stack() {
		reset();
	}
	
	void reset() {
		for (int i = 0; i < 10; i++) {
			arr[i] = 0;
		}
		length = 0;
	}
	
	bool push(const int& number) {
		if (length == 10) return false;
		arr[length++] = number;
		return true;
	}

	int pop() {
		if (length == 0) {
			cout << "Stack is empty\n";
			return 0;
		}
		else {
			int result = arr[length - 1];
			arr[length - 1] = 0;
			length--;
			return result;
		}
	}

	void print() {
		cout << "( ";
		for (int i = 0; i < length; i++) {
			cout << arr[i] << " ";
		}
		cout << ")\n";
	}

private:
	int arr[10];
	int length; 
};

//End of task 3----------------------------------------------------------------

int main() {
	cout << "Task 1-----------------------------------------------------------------------" << endl;
	Power T1;
	T1.calculate();
	T1.set(9, -0.5);
	T1.calculate();
	cout << "End of task 1----------------------------------------------------------------" << "\n\n";

	cout << "Task 2-----------------------------------------------------------------------" << endl;
	RGBA T2_1;
	T2_1.print();
	RGBA T2_2(24, 190, 69, 200);
	T2_2.print();
	cout << "End of task 2----------------------------------------------------------------" << "\n\n";

	cout << "Task 3-----------------------------------------------------------------------" << endl;
	Stack stack;
	stack.reset();
	stack.print();

	stack.push(3);
	stack.push(7);
	stack.push(5);
	stack.print();

	stack.pop();
	stack.print();
	
	stack.pop();
	stack.pop();
	stack.print();
	cout << "End of task 3----------------------------------------------------------------" << "\n\n";

	return 0;
}
