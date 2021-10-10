#ifndef WALLET_H
#define WALLET_H

#include <iostream>
#include <string>
using namespace std;

struct Money {
	string currency;
	double amount;
};

class Wallet {
private:
	Money* dArray; // A Dynamic Array of Money Structs
	int size; // Size of the Dynamic Array
	int findCurrencyInWallet(const Money& rhs) const; // Life-saver Function

public:
	Wallet(); // Default Constructor
	Wallet(int number); // Constructor #2
	Wallet(const Wallet &); // Deep Copy Constructor
	~Wallet(); // Desctructor
	int getSize() const; // Accessor for size
	Money* getDArray() const; // Accessor for dArray

	// 6 Member Functions
	const Wallet& operator=(const Wallet& rhs); // = operator ( Wallet = Wallet )
	Wallet operator+(const Money & rhs) const; // + operator ( Wallet + Money )
	Wallet operator-(const Money & rhs) const; // - operator ( Wallet - Money )
	const Wallet& operator+=(const Wallet& rhs); // += operator ( Wallet += Wallet )
	bool operator==(const Wallet& rhs); // == operator ( Wallet == Wallet ) 
	bool operator>=(const Money& rhs) const; // >= operator ( checks Wallet.Money.currency >= Money.currency )
};

// Mandatory, Three Free Functions
ostream& operator<<(ostream& output, const Wallet& myWallet); // << operator ( ostream << Wallet )
bool operator<=(const Money& lhs, const Wallet& rhs); // <= operator ( checks Money.currency <= Wallet.Money.currency )
Wallet operator+(const Wallet& lhs, const Wallet& rhs); // + operator ( Wallet + Wallet )

#endif