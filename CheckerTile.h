#include <iostream>
#include <iomanip>  
#include <istream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//TODO - заменить класс CheckerTile на абстрактный класс CheckerPiece и унаследовать от него класс для дамки(King) и обычной пешки (Piece)

#pragma once

#ifndef CHECKERSTILE_H
#define CHECKERSTILE_H

class CheckersTile {
public:
	char value;
	string position;
	vector<CheckersTile*> neighbours; // TODO - создать массив соседей
	CheckersTile();
	CheckersTile(string position);
	CheckersTile(char value,string position);
private:

};

class CheckersTileException {};

#endif
