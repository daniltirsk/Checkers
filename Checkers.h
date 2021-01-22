#pragma once

//TODO - сделать обстрактный класс шашек и унаследовать от него класс чекерсов и русских шашек, либо параметризовать размер поля и систему правил игры
//Предусмотреть переход обычной пешки в дамку
#ifndef CHECKERS_H
#define CHECKERS_H

#include "CheckerTile.h"


class Checkers {
public:
	CheckersTile board[64];
	char turn = 'w';
	Checkers();
	Checkers(const char* filename);
	vector<int> findTurns(int nodeNumber);
	void printBoard();
	void isWin();
	void takeMultiple(int source, vector<string>& road);
private:
	int whiteSteps=0;
	int blackSteps=0;

	void countSteps();
	void makeTurn(int source,int dest);
};

class CheckersException {};

#endif