#include "ydogukan_Yildirim_Dogukan_hw5_Wallet.h"
#include <iostream>

using namespace std;

Wallet::Wallet() { // Constructor
	size = 0;
	dArray = NULL;
}

Wallet::Wallet(int number) { // Constructor #2
	size = number;
	dArray = new Money[number];
}

Wallet::Wallet(const Wallet & copy) { // Deep Copy Constructor
	size = copy.size;
	dArray = new Money[size];

	for (int i = 0; i < size; i++)
	{
		dArray[i] = copy.dArray[i];
	}
}

Wallet::~Wallet() { // Destructor
	size = 0;
	delete[] dArray;
}

int Wallet::getSize() const { // Accessor for size
	return size;
}

Money* Wallet::getDArray() const { // Accessor for dArray
	return dArray;
}

/* Begin: code taken and updated from MathVector.cpp */
const Wallet& Wallet::operator=(const Wallet& rhs) { // = operator (assignment)
	if (this != &rhs) {
		size = 0;
		delete[] dArray;

		size = rhs.size;
		dArray = new Money[size];

		for (int i = 0; i < size; i++) {
			dArray[i] = rhs.dArray[i];
		}
	}

	return *this;
}
/* End: code taken and updated from MathVector.cpp */

int Wallet::findCurrencyInWallet(const Money& rhs) const { // Life-saver Function
	// Given a Money struct, returns the index of the Money struct that has the same currency in dArray
	// Returns -1 if the given currency does not exist in dArray
	for (int i = 0; i < size; i++) {
		if (dArray[i].currency == rhs.currency) {
			return i;
		}
	}

	return -1;
}

Wallet Wallet::operator+(const Money& rhs) const{ // + operator
	// Given a Money struct, adds the given amount of money (corresponding to the same currency) to the Wallet
	int index = findCurrencyInWallet(rhs); // Checking whether the given currency is already in dArray

	if (index != -1) { // If the given currency exists in dArray
		Wallet result(*this); // Deep copy the original wallet
		result.dArray[index].amount += rhs.amount; // Add the given amount of money to the copy
		return result; // Return the copy
	}

	else { // Else, meaning that the given currency does not (yet) exist in dArray
		Wallet result(size + 1); // Create a Wallet with one more space for our newcoming currency :)

		for (int i = 0; i < result.size - 1; i++) { // Deep Copy
			result.dArray[i] = dArray[i];
		}

		result.dArray[result.size - 1] = rhs; // Assign the Money Struct to the extra space that was created
		return result;
	}
}

Wallet Wallet::operator-(const Money& rhs) const{ // - operator
	// Subtracts the amount of money in the Money struct from amount of money in the Wallet with the corresponding currency
	// If the amount of money to be subtracted is larger than the amount of money in the Wallet, returns a Wallet without any changes made
	int index = findCurrencyInWallet(rhs); // Checking whether the given currency is already in dArray

	if (size != 0 && dArray[index].amount >= rhs.amount) { // If the non-empty wallet has money more than or equal to the Money Struct with the same currency
		if (dArray[index].amount != rhs.amount) { // If the money amounts are not equal (i.e. when we subtract, we won't get 0)
			Wallet result(*this); // Deep copy
			result.dArray[index].amount -= rhs.amount; // Subtract the amount of money
			return result;
		}

		else { // The money amounts are equal, i.e. there won't be any amount of money left with the given currency
			Wallet result(size - 1); // Preparing to say our goodbyes to the currency by creating a Wallet with size - 1

			// This is kind of tricky, these lines of code basically do the following:
			// Copies over the Money Structs to the dArray of result, IF the amount of money in them is NOT 0
			int i = 0, j = 0;
			while (i < result.size) {
				if (j != index) {
					result.dArray[i] = dArray[j];
					i++;
				}
				j++;
			}

			return result;
		}
	}

	// Else, i.e. if we are trying to spend more than we have, don't touch anything
	return *this;
}

const Wallet & Wallet::operator+=(const Wallet& rhs) { // += operator, adds one Wallet to another and assigns the sum
	for (int i = 0; i < rhs.size; i++) {
		*this = *this + rhs.dArray[i];
	}

	return *this;
}

bool Wallet::operator==(const Wallet& rhs) { // == operator, returns true if the Wallets are the same without checking the order of the Money structs
	if (size == rhs.size) { // Checking whether two Wallets have the same size first
		for (int i = 0; i < size; i++) { // Then with this for loop, checking if two Wallets are the exact same
			int index = findCurrencyInWallet(rhs.dArray[i]);

			if (index == -1) { // If a given currency does not exist in the Wallet
				return false;
			}
			
			else {
				if (dArray[index].currency != rhs.dArray[i].currency || dArray[index].amount != rhs.dArray[i].amount) { // If the amounts of money are not the same with the same currency
					return false;
				}
			}
		}

		return true;
	}

	return false;
}

bool Wallet::operator>=(const Money& rhs) const { // >= operator
	// Returns true if the amount of money in the Wallet is larger than or equal to the amount of money in the Money struct with the corresponding currency, returns false otherwise
	int index = findCurrencyInWallet(rhs);

	if (index != -1) {
		if (dArray[index].amount >= rhs.amount) {
			return true;
		}
	}

	return false;
}

/* Begin: code taken and updated from clockt.cpp */
Wallet operator+(const Wallet& lhs, const Wallet& rhs) { // + operator, adds two Wallets
	Wallet result(lhs);
	result += rhs;
	return result;
}
/* End: code taken and updated from clockt.cpp */

ostream& operator<<(ostream& output, const Wallet& myWallet) { // << operator, allows easy Wallet printing
	Money* myArray = myWallet.getDArray();

	if (myWallet.getSize() != 0) { // Can't try to access an empty Wallet's data, thus need to check it first
		output << myArray[0].currency << " " << myArray[0].amount;

		for (int i = 1, size = myWallet.getSize(); i < size; i++) {
			output << " - " << myArray[i].currency << " " << myArray[i].amount;
		}
	}

	return output;
}

bool operator<=(const Money& lhs, const Wallet& rhs) { // <= operator
	// Returns true if the amount of money in the Money struct is smaller than or equal to the amount of money in the Wallet with the corresponding currency, returns false otherwise
	return rhs >= lhs;
}