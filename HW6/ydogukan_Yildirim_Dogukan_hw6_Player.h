#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "ydogukan_Yildirim_Dogukan_hw6_Board.h"

using namespace std;

template <class type>
class Player {
private:
	Board<type> & board;
	int score;
public:
	Player(Board<type>& matrix); // Parametric Constructor
	type openCard(int row, int column);
	bool validMove(int row, int column);
	void increaseNumberOfSuccess();
	int getNumberOfSuccess();
};

#include "ydogukan_Yildirim_Dogukan_hw6_Player.cpp"
#endif