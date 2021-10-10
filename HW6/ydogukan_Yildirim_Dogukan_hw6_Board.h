#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

template <class type>
struct Card {
	type value;
	bool closed;

	Card() : closed(true) {};
};

template <class type>
class Board {
private:
	int rows, cols;
	Card<type> ** mat;
public:
	Board(int r, int c); // Parametric Constructor
	~Board(); // Destructor
	void readBoardFromFile(ifstream & input);
	void displayBoard();
	void closeCard(int r, int c);
	int getRow();
	int getColumn();
	type openCard(int row, int column);
	bool isClosed(int row, int column);
};

#include "ydogukan_Yildirim_Dogukan_hw6_Board.cpp"
#endif