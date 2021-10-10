#include "ydogukan_Yildirim_Dogukan_hw6_Player.h"

using namespace std;

template <class type>
Player<type>::Player(Board<type>& matrix) // Parametric Constructor
	: score(0), board(matrix)
{}

template <class type>
type Player<type>::openCard(int row, int column) { // Opens the card at the given position and returns the value it holds
	return board.openCard(row, column);
}

template <class type>
bool Player<type>::validMove(int row, int column) { // Returns true if the card at the position is a valid move to play
	if (row >= board.getRow() || column >= board.getColumn() ||
		row < 0 || column < 0 || !board.isClosed(row, column)) { // Checks if the given row and column is out of the range of the board and if the card is closed or not
		return false;
	}

	return true;
}

template <class type>
void Player<type>::increaseNumberOfSuccess() { // Increments the success score of the player
	score++;
}

template <class type>
int Player<type>::getNumberOfSuccess() { // Returns the success score of the player
	return score;
}