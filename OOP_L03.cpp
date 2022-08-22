// OOP using C++ - Webinar 3 (17.08.2022)
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <string>

using namespace std;

//Task 1------------------------------------------------------------------------------------------------------------------------------------

class Figure {
public:
	Figure() = default;
	virtual ~Figure() {}
	virtual double area() const = 0;
};

class Parallelogram : public Figure {
public:
	Parallelogram() : Length(0), Width(0), Height(0) {};
	Parallelogram(const double& _Length, const double& _Width, const double& _Height) : Length(0), Width(0), Height(0) {
		if (_Length > 0) Length = _Length; 
		else cerr << __FUNCTION__ << ": Length value is not positive\n";
		if (_Width > 0) Width = _Width;
		else cerr << __FUNCTION__ << ": Width value is not positive\n";
		if (_Height > 0) Height = _Height;
		else cerr << __FUNCTION__ << ": Height value is not positive\n";
	}
	virtual ~Parallelogram() {}
	virtual double area() const override { 
		cout << __FUNCTION__ << ": ";
		if (Length > 0 && Width > 0 && Height > 0) return Length * Height;
		else return 0;
	}
	virtual void print() const { 
		cout << __FUNCTION__ << ": Length = " << Length << ", Width = " << Width << ", Height = " << Height << endl; 
	}
protected:
	double Length;
	double Width;
	double Height;
};


class Circle : public Figure {
public: 
	Circle() : Radius(0) {}
	Circle(const double& _Radius) : Radius(0) {
		if (_Radius > 0) Radius = _Radius;
		else cerr << __FUNCTION__ << ": Radius value is not positive\n";
	}
	virtual ~Circle() {}
	virtual double area() const override { 
		cout << __FUNCTION__ << ": ";
		if (Radius > 0) return 3.14 * Radius * Radius;
		else return 0;
	}
	virtual void print() const { cout << __FUNCTION__ << ": Radius = " << Radius << endl; }
protected:
	double Radius;
};

class Rectangle : public Parallelogram {
public: 
	Rectangle(const double& _Length, const double& _Width) {
		if (_Length > 0) Length = _Length;
		else cerr << __FUNCTION__ << ": Length value is not positive\n";
		if (_Width > 0) Width = _Width;
		else cerr << __FUNCTION__ << ": Width value is not positive\n";
	}
	virtual ~Rectangle() {}
	virtual double area() const override { 
		cout << __FUNCTION__ << ": ";
		if (Length > 0 && Width > 0) return Length * Width;
		else return 0;
	}
	virtual void print() const { cout << __FUNCTION__ << ": Length = " << Length << ", Width = " << Width  << endl; }
};

class Square : public Parallelogram {
public:
	Square(const double& _Length) {
		if (_Length > 0) Length = _Length;
		else cerr << __FUNCTION__ << ": Length value is not positive\n";
	}
	virtual ~Square() {}
	virtual double area() const override { 
		cout << __FUNCTION__ << ": ";
		if (Length > 0) return Length * Length;
		else return 0; 
	}
	virtual void print() const { cout << __FUNCTION__ << ": Length = " << Length << endl; }
};

class Rhombus : public Parallelogram {
public:
	Rhombus(const double& _Length, const double& _Height) {
		if (_Length > 0) Length = _Length;
		else cerr << __FUNCTION__ << ": Length value is not positive\n";
		if (_Height > 0) Height = _Height;
		else cerr << __FUNCTION__ << ": Width value is not positive\n";
	}
	virtual ~Rhombus() {}
	virtual double area() const override {
		cout << __FUNCTION__ << ": ";
		if (Length > 0 && Height > 0) return Length * Height;
		else return 0;
	}
	virtual void print() const { cout << __FUNCTION__ << ": Length = " << Length << ", Height = " << Height << endl; }
};

//End of task 1-----------------------------------------------------------------------------------------------------------------------------


//Task 2------------------------------------------------------------------------------------------------------------------------------------

class Car {
public:
	Car() { cout << __FUNCTION__ << endl; }
	virtual ~Car() {}
protected:
	string company;
	string model;
};

class PassengerCar : virtual public Car {
public:
	PassengerCar() { cout << __FUNCTION__ << endl; }
	virtual ~PassengerCar() {}
};

class Bus : virtual public Car {
public:
	Bus() { cout << __FUNCTION__ << endl; }
	virtual ~Bus() {}
};

class Minivan : public PassengerCar, public Bus {
public:
	Minivan() { cout << __FUNCTION__ << endl; }
	virtual ~Minivan() {}
};

//End of task 2-----------------------------------------------------------------------------------------------------------------------------


//Task 3------------------------------------------------------------------------------------------------------------------------------------

int GCD(const int& x, const int& y) {
	int a = abs(x);
	int b = abs(y);
	while (a > 0 && b > 0) {
		if (a > b) a %= b;
		else b %= a;
	}
	return a + b;
}

void fraction_reduction(int& numerator, int& denominator) {
	int gcd = GCD(numerator, denominator);
	if (gcd > 1) {
		numerator /= gcd;
		denominator /= gcd;
	}
}

void fraction_sign(int& numerator, int& denominator) {
	if (denominator < 0) {
		numerator = -numerator;
		denominator = -denominator;
	}
}

class Fraction {
public:
	Fraction(const int& _numerator, const int& _denominator) : numerator(0), denominator(1) {
		if (_denominator != 0) {
			numerator = _numerator;
			denominator = _denominator;
		}
		else cerr << __FUNCTION__ << ": _denominator value is zero\n";
	}
	~Fraction() {}
	
	Fraction operator+ (const Fraction& right);
	Fraction operator+ (const int& iright);
	Fraction operator- (const Fraction& right);
	Fraction operator- (const int& iright);
	Fraction operator* (const Fraction& right);
	Fraction operator* (const int& iright);
	Fraction operator/ (const Fraction& right);
	Fraction operator/ (const int& iright);
	Fraction operator- ();

	friend bool operator== (const Fraction& left, const Fraction& right); 
	friend bool operator!= (const Fraction& left, const Fraction& right); 
	friend bool operator< (const Fraction& left, const Fraction& right);
	friend bool operator> (const Fraction& left, const Fraction& right);
	friend bool operator<= (const Fraction& left, const Fraction& right);
	friend bool operator>= (const Fraction& left, const Fraction& right);
	friend ostream& operator<< (ostream& left, Fraction right);
private:
	int numerator;
	int denominator;
};

Fraction Fraction::operator+ (const Fraction& right) {
	int temp_numerator = numerator * right.denominator + right.numerator * denominator;
	int temp_denominator = denominator * right.denominator;
	fraction_reduction(temp_numerator, temp_denominator);
	fraction_sign(temp_numerator, temp_denominator);
	return Fraction(temp_numerator, temp_denominator);
}

Fraction Fraction::operator+ (const int& iright) {
	int temp_numerator = numerator + iright * denominator;
	int temp_denominator = denominator;
	fraction_reduction(temp_numerator, temp_denominator);
	fraction_sign(temp_numerator, temp_denominator);
	return Fraction(temp_numerator, temp_denominator);
}

Fraction Fraction::operator- (const Fraction& right) {
	int temp_numerator = numerator * right.denominator - right.numerator * denominator;
	int temp_denominator = denominator * right.denominator;
	fraction_reduction(temp_numerator, temp_denominator);
	fraction_sign(temp_numerator, temp_denominator);
	return Fraction(temp_numerator, temp_denominator);
}

Fraction Fraction::operator- (const int& iright) {
	int temp_numerator = numerator - iright * denominator;
	int temp_denominator = denominator;
	fraction_reduction(temp_numerator, temp_denominator);
	fraction_sign(temp_numerator, temp_denominator);
	return Fraction(temp_numerator, temp_denominator);
}

Fraction Fraction::operator* (const Fraction& right) {
	int temp_numerator = numerator * right.numerator;
	int temp_denominator = denominator * right.denominator;
	fraction_reduction(temp_numerator, temp_denominator);
	fraction_sign(temp_numerator, temp_denominator);
	return Fraction(temp_numerator, temp_denominator);
}

Fraction Fraction::operator* (const int& iright) {
	int temp_numerator = numerator * iright;
	int temp_denominator = denominator;
	fraction_reduction(temp_numerator, temp_denominator);
	fraction_sign(temp_numerator, temp_denominator);
	return Fraction(temp_numerator, temp_denominator);
}

Fraction Fraction::operator/ (const Fraction& right) {
	int temp_numerator = numerator * right.denominator;
	int temp_denominator = denominator * right.numerator;
	fraction_reduction(temp_numerator, temp_denominator);
	fraction_sign(temp_numerator, temp_denominator);
	return Fraction(temp_numerator, temp_denominator);
}

Fraction Fraction::operator/ (const int& iright) {
	int temp_numerator = numerator;
	int temp_denominator = denominator * iright;
	fraction_reduction(temp_numerator, temp_denominator);
	fraction_sign(temp_numerator, temp_denominator);
	return Fraction(temp_numerator, temp_denominator);
}

Fraction Fraction::operator- () {
	int temp_numerator = -numerator;
	int temp_denominator = denominator;
	fraction_sign(temp_numerator, temp_denominator);
	return Fraction(temp_numerator, temp_denominator);
}

bool operator== (const Fraction& left, const Fraction& right) {
	int ltemp_numerator = left.numerator;
	int ltemp_denominator = left.denominator;
	fraction_reduction(ltemp_numerator, ltemp_denominator);
	fraction_sign(ltemp_numerator, ltemp_denominator);

	int rtemp_numerator = right.numerator;
	int rtemp_denominator = right.denominator;
	fraction_reduction(rtemp_numerator, rtemp_denominator);
	fraction_sign(rtemp_numerator, rtemp_denominator);

	return (ltemp_numerator == rtemp_numerator && ltemp_denominator == rtemp_denominator);
}

bool operator!= (const Fraction& left, const Fraction& right) {
	return !(left == right);
}

bool operator< (const Fraction& left, const Fraction& right) {
	int ltemp_numerator = left.numerator;
	int ltemp_denominator = left.denominator;
	fraction_reduction(ltemp_numerator, ltemp_denominator);
	fraction_sign(ltemp_numerator, ltemp_denominator);

	int rtemp_numerator = right.numerator;
	int rtemp_denominator = right.denominator;
	fraction_reduction(rtemp_numerator, rtemp_denominator);
	fraction_sign(rtemp_numerator, rtemp_denominator);
	
	ltemp_numerator *= rtemp_denominator;
	rtemp_numerator *= ltemp_denominator;

	return (ltemp_numerator < rtemp_numerator);
}

bool operator> (const Fraction& left, const Fraction& right) {
	int ltemp_numerator = left.numerator;
	int ltemp_denominator = left.denominator;
	fraction_reduction(ltemp_numerator, ltemp_denominator);
	fraction_sign(ltemp_numerator, ltemp_denominator);

	int rtemp_numerator = right.numerator;
	int rtemp_denominator = right.denominator;
	fraction_reduction(rtemp_numerator, rtemp_denominator);
	fraction_sign(rtemp_numerator, rtemp_denominator);

	ltemp_numerator *= rtemp_denominator;
	rtemp_numerator *= ltemp_denominator;

	return (ltemp_numerator > rtemp_numerator);
}

bool operator>= (const Fraction& left, const Fraction& right) {
	return !(left < right);
}

bool operator<= (const Fraction& left, const Fraction& right) {
	return !(left > right);
}

ostream& operator<< (ostream& left, Fraction right) {
	if (right.numerator == 0) return left << "0";
	else return left << right.numerator << "/" << right.denominator;
}

//End of task 3-----------------------------------------------------------------------------------------------------------------------------


//Task 4------------------------------------------------------------------------------------------------------------------------------------

enum class Suits { Diamonds, Hearts, Clubs, Spades };
enum class Values { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack = 10, Queen = 10, King = 10 };

class Card {
public:
	Card(const Suits& _suit, const Values& _value, const bool& _position) : Suit(_suit), Value(_value), Position(_position) {}
	Values GetValue() const { return Value; }
	void Flip() { 
		if (Position == false) Position = true;
		else Position = false;
	}

	friend void print_Card(const Card& card);

private:
	Suits Suit;
	Values Value; 
	bool Position;
};

void print_Card(const Card& card) {
	cout << "Card: suit = " << (int)card.Suit << ", value = " << (int)card.Value << ", position = " << card.Position << endl;
}

//End of task 4-----------------------------------------------------------------------------------------------------------------------------


int main() {
	cout << "Task 1-------------------------------------------------------------------------------------\n";
	Parallelogram P(30, 15, 10);
	P.print();
	cout << P.area() << endl;
	Circle C(10);
	C.print();
	cout << C.area() << endl;
	Rectangle Rec(20, 10);
	Rec.print();
	cout << Rec.area() << endl;
	Square S(15);
	S.print();
	cout << S.area() << endl;
	Rhombus R(20, 15);
	R.print();
	cout << R.area() << endl;
	cout << "End of task 1------------------------------------------------------------------------------\n\n";


	cout << "Task 2-------------------------------------------------------------------------------------\n";
	Car car; 
	cout << endl;
	PassengerCar pc;
	cout << endl;
	Bus bus;
	cout << endl;
	Minivan m;
	cout << "End of task 2------------------------------------------------------------------------------\n\n";


	cout << "Task 3-------------------------------------------------------------------------------------\n";
	Fraction F1(9, -15), F2(3, 4), F3 (-27, 45), F4 (-75, -100);
	cout << F1 << " + " << F2 << " = " << F1 + F2 << endl; 
	cout << F1 << " + 3 = " << F1 + 3 << endl; 
	cout << F1 << " - " << F2 << " = " << F1 - F2 << endl;
	cout << F1 << " - 2 = " << F1 - 2 << endl;
	cout << F1 << " * " << F2 << " = " << F1 * F2 << endl;
	cout << F1 << " * -4 = " << F1 * -4 << endl;
	cout << F1 << " / " << F2 << " = " << F1 / F2 << endl;
	cout << F1 << " / 6 = " << F1 / 6 << endl;
	cout << "-(" << F1 << ") = " << -F1 << endl;
	cout << "-(" << F2 << ") = " << -F2 << endl;
	cout << F1 << " == " << F2 << ((F1 == F2) ? " is true" : " is false") << endl;
	cout << F1 << " == " << F3 << ((F1 == F3) ? " is true" : " is false") << endl;
	cout << F2 << " != " << F3 << ((F2 != F3) ? " is true" : " is false") << endl;
	cout << F2 << " != " << F4 << ((F2 != F4) ? " is true" : " is false") << endl;
	cout << F1 << " < " << F2 << ((F1 < F2) ? " is true" : " is false") << endl;
	cout << F1 << " < " << F3 << ((F1 < F3) ? " is true" : " is false") << endl;
	cout << F2 << " > " << F3 << ((F2 > F3) ? " is true" : " is false") << endl;
	cout << F2 << " > " << F4 << ((F2 < F4) ? " is true" : " is false") << endl;
	cout << F1 << " >= " << F2 << ((F1 >= F2) ? " is true" : " is false") << endl;
	cout << F1 << " >= " << F3 << ((F1 >= F3) ? " is true" : " is false") << endl;
	cout << F2 << " <= " << F3 << ((F2 <= F3) ? " is true" : " is false") << endl;
	cout << F2 << " <= " << F4 << ((F2 <= F4) ? " is true" : " is false") << endl;
	cout << "End of task 3------------------------------------------------------------------------------\n\n";


	cout << "Task 4-------------------------------------------------------------------------------------\n";
	Card H3(Suits::Hearts, Values::Three, false);
	print_Card(H3);
	H3.Flip();
	print_Card(H3);
	cout << "Card value = " << (int)H3.GetValue() << endl;
	cout << "End of task 4------------------------------------------------------------------------------\n\n";

	return 0;
}
