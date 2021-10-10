#include "ydogukan_Yildirim_Dogukan_hw6_Board.h"

using namespace std;

template <class type>
Board<type>::Board(int r, int c) { // Parametric Constructor
	rows = r;
	cols = c;
	mat = new Card<type>*[rows];

	for (int i = 0; i < rows; i++) {
		mat[i] = new Card<type>[cols];
	}
}

template <class type>
Board<type>::~Board() { // Destructor
	for (int i = 0; i < rows; i++) {
		delete[] mat[i];
		mat[i] = NULL;
	}
	delete[] mat;
	mat = NULL;
}

template <class type>
void Board<type>::readBoardFromFile(ifstream & input) { // Fills the matrix/board with the values coming from filestream
	string line;
	type value;
		
	for (int i = 0; i < rows; i++) {
		getline(input, line);
		istringstream values(line);

		for (int j = 0; j < cols; j++) {
			values >> value;
			mat[i][j].value = value;
		}
	}
}

template <class type>
void Board<type>::displayBoard() { // Prints out the matrix/board
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (mat[i][j].closed == true) {
				cout << "X" << "  ";
			}
			
			else {
				cout << mat[i][j].value << "  ";
			}
		}

		cout << endl;
	}
}

template <class type>
void Board<type>::closeCard(int row, int column) { // Given a position, closes the card at that position in the matrix
	mat[row][column].closed = true;
}

template <class type>
int Board<type>::getRow() { // Returns the number of rows of the board
	return rows;
}

template <class type>
int Board<type>::getColumn() { // Returns the number of columns of the board
	return cols;
}

template <class type>
type Board<type>::openCard(int row, int column) { // Helper member function for Player class, opens the card at the given position and returns the value it holds
	mat[row][column].closed = false;
	return mat[row][column].value;
}

template <class type>
bool Board<type>::isClosed(int row, int column) { // Returns true if the card at the given position is closed
	return mat[row][column].closed;
}