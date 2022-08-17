// OOP using C++ - Webinar 2 (15.08.2022)
// Homework - tasks 1 and 2
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <string>

using namespace std;

//Task 1------------------------------------------------------------------------------------------------------------------------------------

class Person {
public:
	Person(const string& _Name, const int& _Age, const char& _Gender, const double& _Weight) 
		: Name(_Name), Age (0), Gender('-'), Weight(0) {
		if (_Age >= 0) Age = _Age; 
		else cerr << __FUNCTION__ << ": _Age value is less than 0\n";
		if (_Gender == 'F' || _Gender == 'M') Gender = _Gender; 
		else cerr << __FUNCTION__ << ": _Gender value is invalid\n";
		if (_Weight > 0) Weight = _Weight; 
		else cerr << __FUNCTION__ << ": _Weight value is not positive\n";
	}
	
	~Person() {};
	
	void setName(const string& _Name) { Name = _Name; }

	void setAge(const int& _Age) { 
		if (_Age >= 0) Age = _Age; 
		else cerr << __FUNCTION__ << ": _Age value is less than 0\n"; 
	}

	void setWeight(const double& _Weight) { 
		if (_Weight > 0) Weight = _Weight; 
		else cerr << __FUNCTION__ << ": _Weigth value is not positive\n"; 
	}
	
	void print() const { cout << Name << ", " << Age << ", " << Gender << ", " << Weight << endl; }

protected:
	string Name;
	int Age;
	char Gender;
	double Weight;
};

int Student_counter{ 0 };

class Student : public Person {
public:
	Student (const string& _Name, const int& _Age, const char& _Gender, const double& _Weight, const int& _Year_of_study) 
		: Person(_Name, _Age, _Gender, _Weight), Year_of_study(0) {
		if (_Year_of_study > 0) Year_of_study = _Year_of_study;
		else cerr << __FUNCTION__ << ": _Year_of_study value is not positive\n";
		Student_counter++;
	}
	
	~Student() {}
	
	void setYear_of_study(const int& _Year_of_study) {
		if (_Year_of_study > 0) Year_of_study = _Year_of_study;
		else cerr << __FUNCTION__ << ": _Year_of_study value is not positive\n";
	}
	
	void addYear_of_study(const int& _Years) {
		if (_Years >= 0) Year_of_study += _Years;
		else cerr << __FUNCTION__ << ": _Years value is less than 0\n";
	}
	
	void print() const { cout << Name << ", " << Age << ", " << Gender << ", " << Weight << ", " << Year_of_study << endl; }

private:
	int Year_of_study; 
};

//End of task 1-----------------------------------------------------------------------------------------------------------------------------


//Task 2------------------------------------------------------------------------------------------------------------------------------------

class Fruit {
public:
	Fruit(const string& _Name) : Name(_Name), Color("") {}
	Fruit(const string& _Name, const string& _Color) : Name(_Name), Color(_Color) {}
	~Fruit() {}
	void setName(const string& _Name) { Name = _Name; }
	void setColor(const string& _Color) { Color = _Color; }
	string getName() const { return Name; }
	string getColor() const { return Color; }
protected:
	string Name;
	string Color;
};

class Apple : public Fruit {
public:
	Apple() : Fruit("apple"), Variety("") {}
	Apple(const string& _Color) : Fruit("apple", _Color), Variety("") {}
	Apple(const string& _Color, const string& _Variety) : Fruit("apple", _Color), Variety(_Variety) {}
	~Apple() {}
	void setVariety(const string& _Variety) { Variety = _Variety; }
	string getName() const { return Name; }
	string getColor() const { return Color; }
	string getVariety() const { return Variety; }
protected:
	string Variety;
};

class Banana : public Fruit {
public:
	Banana() : Fruit("banana", "yellow"), Variety("") {}
	Banana(const string& _Color) : Fruit("banana", _Color), Variety("") {}
	Banana(const string& _Color, const string& _Variety) : Fruit("banana", _Color), Variety(_Variety) {}
	~Banana() {}
	void setVariety(const string& _Variety) { Variety = _Variety; }
	string getName() const { return Name; }
	string getColor() const { return Color; }
	string getVariety() const { return Variety; }
protected:
	string Variety;
};

class GrannySmith : public Apple {
public:
	GrannySmith() : Apple("green", "Granny Smith") {}
	~GrannySmith() {}
	string getName() const { return (Variety + " " + Name); }
	string getColor() const { return Color; }
};

//End of task 2-----------------------------------------------------------------------------------------------------------------------------


int main() {
	cout << "Task 1-------------------------------------------------------------------------------------\n";
	cout << "Student counter value: " << Student_counter << endl;
	Student S1("Alex", 27, 'M', 75.3, 2), S2("Marie", 28, 'F', 54.7, 1), S3("Anna", 27, 'F', 56.1, 1);
	S2.setYear_of_study(4);
	S3.addYear_of_study(2);
	S1.print();
	S2.print();
	S3.print();
	cout << "Student counter value: " << Student_counter << endl;
	cout << "End of task 1------------------------------------------------------------------------------\n\n";

	cout << "Task 2-------------------------------------------------------------------------------------\n";
	Apple a("red");
	Banana b;
	GrannySmith c;
	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
	cout << "End of task 2------------------------------------------------------------------------------\n\n";

	return 0;
}


//Task 3------------------------------------------------------------------------------------------------------------------------------------
/*
enum class Card_values { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack = 10, Queen = 10, King = 10, Ace = 11, Reverse = 0 };

enum class Suits { Reverse, Diamonds, Hearts, Clubs, Spades };

class Card_set {
public: 
	Card_set() : Score(0) {} 
	Card_set(const Card_values& _Card_value) : Score(static_cast<int>(_Card_value)) {}
	~Card_set() {}
	int getScore() const { return Score; }
	void addScore(const int& _Score) {
		if (_Score < 11) Score += _Score;
		else {
			if ((Score + _Score) <= 21) Score += _Score;
			else Score++;
		}
	}
	bool isOver() { return (Score > 21) ? true : false; }
protected:
	int Score;
};

class Card : public Card_set {
public:
	Card() : Card_set(Card_values::Reverse), Card_value(Card_values::Reverse), Suit(Suits::Reverse) {}
	Card (const Card_values& _Card_value, const Suits& _Suit) : Card_set(_Card_value), Card_value(_Card_value), Suit(_Suit) {}
	~Card() {}
	Card_values getCard_value() const { return Card_value; }
	Suits getSuit() const { return Suit; }
	int getCard_score() const { return static_cast<int>(Card_value); }
protected:
	Card_values Card_value;
	Suits Suit;

};

Card NewCard() {

}

void Deal() {

}

void AddCardToHand(const Card_set& _Hand, const Card& _Card) {

}

void Double() {

}

void GameStatus() {

}

void Game() {
	Card_set Player_hand, Dealer_hand;
	
}
*/

//End of task 3-----------------------------------------------------------------------------------------------------------------------------
