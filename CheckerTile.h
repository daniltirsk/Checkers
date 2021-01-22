#include <iostream>
#include <iomanip>  
#include <istream>
#include <fstream>
#include <string>

using namespace std;

#pragma once

#ifndef CHECKERSTILE_H
#define CHECKERSTILE_H

class CheckersTile {
public:
	char value;
	string position;
	CheckersTile();
	CheckersTile(string position);
	CheckersTile(char value,string position);
private:

};

class CheckersTileException {};

#endif
