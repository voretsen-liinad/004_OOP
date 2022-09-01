// OOP using C++ - Webinar 6 (29.08.2022)
// Homework - tasks 3, 4, 5 (Black Jack)
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <Windows.h> //this line to deal with incorrect suits chars screen output - on author's computer does not work :(

using namespace std;

enum class Suits { Diamonds, Hearts, Clubs, Spades };
enum class Values { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

class Card {
public:
	Card(const Suits& _suit, const Values& _value, const bool& _position) : Suit(_suit), Value(_value), Position(_position) {}
	~Card() {}
	Values GetValue() const { return Value; }
	void Flip() {
		if (Position == false) Position = true;
		else Position = false;
	}

//Task 5 (part 1)---------------------------------------------------------------------------------------------------------------------------

	friend ostream& operator<< (ostream& os, const Card& _card);
	static const char suits[4];
	static vector<string> values;
protected:
	Suits Suit;
	Values Value;
	bool Position;
};

const char Card::suits[4] = { 0x04, 0x03, 0x05, 0x06 };
vector<string> Card::values = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

ostream& operator<< (ostream& os, const Card& _card) {
	if (_card.Position == false) return os << "XX";
	else return os << Card::suits[(int)_card.Suit] << Card::values[(int)_card.GetValue()-1];
}

//End of task 5 (part 1)--------------------------------------------------------------------------------------------------------------------


class Hand {
public:
	Hand() {}
	~Hand() {}
	void Add(Card* _card) { Cards.push_back(_card); }
	void Clear() { Cards.clear(); }
	int GetValue() const {
		if (Cards.size() == 0) return 0;
		else {
			int result = 0;
			int current_value = 0;
			int ace_counter = 0;
			for (int i = 0; i < Cards.size(); i++) {
				current_value = (int)Cards[i]->GetValue();
				if (current_value == 1) ace_counter++;
				if (current_value == 11 || current_value == 12 || current_value == 13) current_value = 10;
				result += current_value;
			}
			if (ace_counter > 0) {
				if (ace_counter == 2 && Cards.size() == 2) return 21; //Two Aces equal 21 points
				else if (result <= 11) result += 10; //Ace has 11 points if that is good
			}
			return result;
		}
	}
protected:
	vector<Card*> Cards;
};


class GenericPlayer : public Hand {
public:
	GenericPlayer(const string& _name) : Name(_name) {}
	~GenericPlayer() {}
	virtual bool IsHitting() const = 0;
	bool IsBoosted() const {
		if (GetValue() > 21) return true;
		else return false;
	}
	void Bust() const { cout << Name << " has bust\n"; }

//Task 5 (part 2)---------------------------------------------------------------------------------------------------------------------------

	friend ostream& operator<< (ostream& os, const GenericPlayer& _player);
protected:
	string Name;
};

ostream& operator<< (ostream& os, const GenericPlayer& _player) {
	os << _player.Name << ": ";
	for (int i = 0; i < _player.Cards.size(); i++) {
		os << *(_player.Cards[i]) << " ";
	}
	os << " - " << _player.GetValue() << " point(s)";
	return os;
}

//End of task 5 (part 2)--------------------------------------------------------------------------------------------------------------------



//Task 3------------------------------------------------------------------------------------------------------------------------------------

class Player : public GenericPlayer {
public:
	Player(const string& _name) : GenericPlayer(_name) {}
	~Player() {}
	virtual bool IsHitting() const override {
		while (true) {
			cout << "Do you need another card? (y/n): ";
			string s;
			getline(cin, s);
			if (s.size() == 0 || s.size() > 1 || (s != "y" && s != "Y" && s != "n" && s != "N")) cerr << "Incorrect input, try again\n";
			else {
				if (s == "y" || s == "Y") return true;
				else return false;
			}
		}
	}
	void Win() const { cout << Name << " won :)\n"; }
	void Lose() const { cout << Name << " lost :(\n"; }
	void Push() const { cout << Name << " tied :|\n"; }
};

//End of task 3-----------------------------------------------------------------------------------------------------------------------------


//Task 4------------------------------------------------------------------------------------------------------------------------------------

class House : public GenericPlayer {
public:
	House() : GenericPlayer("House") {}
	~House() {}
	virtual bool IsHitting() const override {
		if (GetValue() < 17) return true;
		else return false;
	}
	void FlipFirstCard() { Cards[0]->Flip(); }
};

//End of task 4-----------------------------------------------------------------------------------------------------------------------------



int main() {  //to compile and run current code pure virtual function "IsHitting()" of the class "GenericPlayer" must be removed 	
	setlocale(LC_ALL, "rus"); //this line to deal with incorrect suits chars screen output - on author's computer does not work :( 
	SetConsoleOutputCP(1251); //this line to deal with incorrect suits chars screen output - on author's computer does not work :(
	SetConsoleCP(1251); //this line to deal with incorrect suits chars screen output - on author's computer does not work :(

	Card D5(Suits::Diamonds, Values::Five, true);
	Card HJ(Suits::Hearts, Values::Jack, true);
	Card SQ(Suits::Spades, Values::Queen, true);
	Card HA(Suits::Hearts, Values::Ace, true);
	Card CA(Suits::Clubs, Values::Ace, true);

	cout << "Task 3-------------------------------------------------------------------------------------\n";
	Player P("Sophie"); 
	cout << setiosflags(ios_base::boolalpha) << P.IsHitting() << endl;
	P.Win();
	P.Lose();
	P.Push();
	cout << endl;
	cout << "End of task 3------------------------------------------------------------------------------\n\n";

	cout << "Task 4-------------------------------------------------------------------------------------\n";
	House H;
	H.Add(&HJ);
	H.Add(&D5); 
	H.Add(&CA);
	cout << H.GetValue() << endl;
	cout << setiosflags(ios_base::boolalpha) << H.IsHitting() << endl;
	cout << endl;
	cout << "End of task 4------------------------------------------------------------------------------\n\n";

	cout << "Task 5-------------------------------------------------------------------------------------\n";
	cout << SQ << endl;
	cout << H << endl;
	cout << endl;
	cout << "End of task 5------------------------------------------------------------------------------\n\n";

	return 0;
}
