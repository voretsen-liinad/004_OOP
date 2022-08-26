// OOP using C++ - Webinar 5 (25.08.2022)
// Homework - tasks 4 (Black Jack)
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <vector>

using namespace std;

enum class Suits { Diamonds, Hearts, Clubs, Spades };
enum class Values { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack = 10, Queen = 10, King = 10 };

class Card {
public:
	Card(const Suits& _suit, const Values& _value, const bool& _position) : Suit(_suit), Value(_value), Position(_position) {}
	~Card() {}
	Values GetValue() const { return Value; }
	void Flip() {
		if (Position == false) Position = true;
		else Position = false;
	}
private:
	Suits Suit;
	Values Value;
	bool Position;
};


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
				result += current_value;
			}
			if (ace_counter > 0) {
				if (ace_counter == 2 && Cards.size() == 2) return 21; //Two Aces equal 21 points
				else if (result <= 11) result += 10; //Ace has 11 points if that is good
			}
			return result;
		}
	}
private:
	vector<Card*> Cards;
};


//Task 4------------------------------------------------------------------------------------------------------------------------------------

class GenericPlayer : public Hand {
public:
	GenericPlayer(const string& _name) : Name(_name) {}
	~GenericPlayer() {}
	//virtual bool IsHitting() = 0;  //this pure virtual function is removed to compile and run current code
	bool IsBoosted() const {
		if (GetValue() > 21) return true;
		else return false;
	}
	void Bust() const {	cout << Name << " has bust\n"; }
private:
	string Name;
};

//End of task 4-----------------------------------------------------------------------------------------------------------------------------


int main() {  //to compile and run current code pure virtual function "IsHitting()" of the class "GenericPlayer" must be removed 
	cout << "Task 4-------------------------------------------------------------------------------------\n";
	Card D5(Suits::Diamonds, Values::Five, true);
	Card HJ(Suits::Hearts, Values::Jack, true);
	Card SQ(Suits::Spades, Values::Queen, true);
	Card HA(Suits::Hearts, Values::Ace, true);
	Card CA(Suits::Clubs, Values::Ace, true);

	GenericPlayer P("Sophie");

	P.Add(&HJ);
	P.Add(&SQ);
	cout << P.GetValue() << endl;
	if (P.IsBoosted()) P.Bust();
	P.Add(&CA);
	cout << P.GetValue() << endl;
	if (P.IsBoosted()) P.Bust();
	P.Add(&HA);
	cout << P.GetValue() << endl;
	if (P.IsBoosted()) P.Bust();

	cout << "End of task 4------------------------------------------------------------------------------\n\n";

	return 0;
}
