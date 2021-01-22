#include "CheckerTile.h"

CheckersTile::CheckersTile() {
	this->value = 'e';
	this->position = "";
}

CheckersTile::CheckersTile(string position) {
	this->value = 'e';
	this->position = position;
}

CheckersTile::CheckersTile(char value,string position) {
	this->value = value;
	this->position = position;
}