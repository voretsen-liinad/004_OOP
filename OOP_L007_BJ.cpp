// OOP using C++ - Webinar 7 (01.09.2022)
// Homework - tasks 3, 4, 5 (Black Jack)
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

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
	friend ostream& operator<< (ostream& os, const Card& _card);
	static const char suits[4];
	static vector<string> values;
protected:
	Suits Suit;
	Values Value;
	bool Position;
};

//const char Card::suits[4] = { 0x04, 0x03, 0x05, 0x06 }; //this chars don't screen correctly on my computer
const char Card::suits[4] = { 'D', 'H', 'C', 'S'};
vector<string> Card::values = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

ostream& operator<< (ostream& os, const Card& _card) {
	if (_card.Position == false) return os << "XX";
	else return os << Card::suits[(int)_card.Suit] << Card::values[(int)_card.GetValue() - 1];
}


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
	void Bust() const { cout << Name << " has bust."; }
	friend ostream& operator<< (ostream& os, const GenericPlayer& _player);
protected:
	string Name;
};

ostream& operator<< (ostream& os, const GenericPlayer& _player) {
	os << _player.Name << ": ";
	for (int i = 0; i < _player.Cards.size(); i++) {
		os << *(_player.Cards[i]) << " ";
	}
	os << " - " << _player.GetValue() << " point(s).";
	return os;
}


class Player : public GenericPlayer {
public:
	Player(const string& _name) : GenericPlayer(_name) {}
	~Player() {}
	virtual bool IsHitting() const override {
		while (true) {
			cout << Name <<": Do you need another card? (y/n): ";
			string s;
			getline(cin, s);
			if (s.size() == 0 || s.size() > 1 || (s != "y" && s != "Y" && s != "n" && s != "N")) cerr << "Incorrect input, try again\n";
			else {
				if (s == "y" || s == "Y") return true;
				else return false;
			}
		}
	}
	void Win() const { cout << Name << " won :)"; }
	void Lose() const { cout << Name << " lost :("; }
	void Push() const { cout << Name << " pushed :|"; }
};


class House : public GenericPlayer {
public:
	House() : GenericPlayer("House") {}
	~House() {}
	virtual bool IsHitting() const override {
		if (GetValue() < 17) return true;
		else return false;
	}
	void FlipFirstCard() { Cards[0]->Flip(); }
	void HouseFirstPrint() {
		cout << Name << ": " << *Cards[0] << " " << *Cards[1];
	}
};


//Task 3------------------------------------------------------------------------------------------------------------------------------------

class Deck : public Hand {
public:
	Deck() { Populate(); }
	~Deck() {}
	void Populate();
	void Shuffle() {
		srand(time(0));
		random_shuffle(Cards.begin(), Cards.end());
	}
	void Deal(Hand& aHand) {
		if (Cards.size() == 0) {
			Populate();
			Shuffle();
		}
		aHand.Add(Cards[Cards.size() - 1]);
		Cards.pop_back();
	}
	void AdditionalCards(GenericPlayer& aGenericPlayer) {
		while (aGenericPlayer.GetValue() < 21 && !aGenericPlayer.IsBoosted() && aGenericPlayer.IsHitting()) {
			Deal(aGenericPlayer);
			cout << aGenericPlayer << " ";
			if (aGenericPlayer.IsBoosted()) aGenericPlayer.Bust();
			cout << endl;
		}
		cout << endl;
	}
};

void Deck::Populate() {
	Add(new Card(Suits::Diamonds, Values::Ace, true));
	Add(new Card(Suits::Diamonds, Values::Two, true));
	Add(new Card(Suits::Diamonds, Values::Three, true));
	Add(new Card(Suits::Diamonds, Values::Four, true));
	Add(new Card(Suits::Diamonds, Values::Five, true));
	Add(new Card(Suits::Diamonds, Values::Six, true));
	Add(new Card(Suits::Diamonds, Values::Seven, true));
	Add(new Card(Suits::Diamonds, Values::Eight, true));
	Add(new Card(Suits::Diamonds, Values::Nine, true));
	Add(new Card(Suits::Diamonds, Values::Ten, true));
	Add(new Card(Suits::Diamonds, Values::Jack, true));
	Add(new Card(Suits::Diamonds, Values::Queen, true));
	Add(new Card(Suits::Diamonds, Values::King, true));

	Add(new Card(Suits::Hearts, Values::Ace, true));
	Add(new Card(Suits::Hearts, Values::Two, true));
	Add(new Card(Suits::Hearts, Values::Three, true));
	Add(new Card(Suits::Hearts, Values::Four, true));
	Add(new Card(Suits::Hearts, Values::Five, true));
	Add(new Card(Suits::Hearts, Values::Six, true));
	Add(new Card(Suits::Hearts, Values::Seven, true));
	Add(new Card(Suits::Hearts, Values::Eight, true));
	Add(new Card(Suits::Hearts, Values::Nine, true));
	Add(new Card(Suits::Hearts, Values::Ten, true));
	Add(new Card(Suits::Hearts, Values::Jack, true));
	Add(new Card(Suits::Hearts, Values::Queen, true));
	Add(new Card(Suits::Hearts, Values::King, true));

	Add(new Card(Suits::Clubs, Values::Ace, true));
	Add(new Card(Suits::Clubs, Values::Two, true));
	Add(new Card(Suits::Clubs, Values::Three, true));
	Add(new Card(Suits::Clubs, Values::Four, true));
	Add(new Card(Suits::Clubs, Values::Five, true));
	Add(new Card(Suits::Clubs, Values::Six, true));
	Add(new Card(Suits::Clubs, Values::Seven, true));
	Add(new Card(Suits::Clubs, Values::Eight, true));
	Add(new Card(Suits::Clubs, Values::Nine, true));
	Add(new Card(Suits::Clubs, Values::Ten, true));
	Add(new Card(Suits::Clubs, Values::Jack, true));
	Add(new Card(Suits::Clubs, Values::Queen, true));
	Add(new Card(Suits::Clubs, Values::King, true));

	Add(new Card(Suits::Spades, Values::Ace, true));
	Add(new Card(Suits::Spades, Values::Two, true));
	Add(new Card(Suits::Spades, Values::Three, true));
	Add(new Card(Suits::Spades, Values::Four, true));
	Add(new Card(Suits::Spades, Values::Five, true));
	Add(new Card(Suits::Spades, Values::Six, true));
	Add(new Card(Suits::Spades, Values::Seven, true));
	Add(new Card(Suits::Spades, Values::Eight, true));
	Add(new Card(Suits::Spades, Values::Nine, true));
	Add(new Card(Suits::Spades, Values::Ten, true));
	Add(new Card(Suits::Spades, Values::Jack, true));
	Add(new Card(Suits::Spades, Values::Queen, true));
	Add(new Card(Suits::Spades, Values::King, true));

}

//End of task 3-----------------------------------------------------------------------------------------------------------------------------


//Task 4------------------------------------------------------------------------------------------------------------------------------------

class Game {
public:
	Game(const vector<string>& names) {
		int Players_number = names.size();
		for (int i = 0; i < Players_number; i++) {
			thePlayers.push_back(Player(names[i]));
		}
		theDeck = Deck();
		theDeck.Shuffle();
	}
	~Game() { thePlayers.clear(); }
	void play();
private:
	Deck theDeck;
	House theHouse;
	vector<Player> thePlayers;
};

void Game::play() {
	int Players_number = thePlayers.size();
	for (int i = 0; i < Players_number; i++) {
		theDeck.Deal(thePlayers[i]);
	}
	theDeck.Deal(theHouse);
	theHouse.FlipFirstCard();
	for (int i = 0; i < Players_number; i++) {
		theDeck.Deal(thePlayers[i]);
	}
	theDeck.Deal(theHouse);

	for (int i = 0; i < Players_number; i++) {
		cout << thePlayers[i] << endl;
	}
	theHouse.HouseFirstPrint();
	cout << "\n" << endl;

	for (int i = 0; i < Players_number; i++) {
		if (thePlayers[i].GetValue() < 21) theDeck.AdditionalCards(thePlayers[i]);
	}
	theHouse.FlipFirstCard();
	cout << theHouse << endl;
	theDeck.AdditionalCards(theHouse);

	for (int i = 0; i < Players_number; i++) {
		cout << thePlayers[i] << " ";
		if (thePlayers[i].IsBoosted()) {
			thePlayers[i].Bust();
			cout << " ";
			thePlayers[i].Lose();
		}
		else {
			if (theHouse.IsBoosted() || (!theHouse.IsBoosted() && thePlayers[i].GetValue() > theHouse.GetValue())) {
				thePlayers[i].Win();
			}
			else {
				if (!theHouse.IsBoosted() && thePlayers[i].GetValue() < theHouse.GetValue()) {
					thePlayers[i].Lose();
				}
				else thePlayers[i].Push();
			}
		}
		cout << endl;
	}
	cout << theHouse << " ";
	if (theHouse.IsBoosted()) theHouse.Bust();
	cout << endl;

	for (int i = 0; i < Players_number; i++) {
		thePlayers[i].Clear();
	}
	theHouse.Clear();
}

//End of task 4-----------------------------------------------------------------------------------------------------------------------------


int main() {  	

//Task 5------------------------------------------------------------------------------------------------------------------------------------
	
	char to_play{ 'y' };
	while (to_play == 'y' || to_play == 'Y') {
		cout << "The BlackJack game.\n";
		vector<string> players;
		int current_number{ 0 };
		while (current_number < 9) {
			string current_name;
			cout << "Please, input a name of Player " << current_number + 1;
			if (current_number == 0) {
				cout << ": ";
				getline(cin, current_name);
				if (current_name.size() == 0) {
					cerr << "There must be at least one player. Try again.\n";
					continue;
				}
				else players.push_back(current_name);
				current_number++;
			}
			else {
				cout << ", or press enter to end input: ";
				getline(cin, current_name);
				if (current_name.size() == 0) break;
				else players.push_back(current_name);
				current_number++;
			}
		}
		cout << "\nThe game has started.\n\n";
		unique_ptr<Game> ptrGame(new Game(players));
		ptrGame->play(); 
		cout << "\nWould you like to start a new game? If yes input \"y\", or any other char to exit: ";
		cin >> to_play;
	}

//End of task 5-----------------------------------------------------------------------------------------------------------------------------


	return 0;
}
