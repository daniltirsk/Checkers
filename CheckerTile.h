#include <iostream>
#include <iomanip>  
#include <istream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//TODO - �������� ����� CheckerTile �� ����������� ����� CheckerPiece � ������������ �� ���� ����� ��� �����(King) � ������� ����� (Piece)

#pragma once

#ifndef CHECKERSTILE_H
#define CHECKERSTILE_H

class CheckersTile {
public:
	char value;
	string position;
	vector<CheckersTile*> neighbours; // TODO - ������� ������ �������
	CheckersTile();
	CheckersTile(string position);
	CheckersTile(char value,string position);
private:

};

class CheckersTileException {};

#endif
