#include <iostream>
#include <iomanip>  
#include <istream>
#include <fstream>
#include <string>
#include <vector>

#include "Checkers.h"

using namespace std;

Checkers::Checkers() {
	char letter = 'A';
	char number = '1';
	string position;
	for (int i = 0; i < 8; i++)
	{
		letter = 'A';
		for (int j = 0; j < 8; j++)
		{	
			position = "";
			position += letter;
			position += number;
			this->board[i*8+j].value = 'e';
			this->board[i*8+j].position = position;
			letter++;
		}
		number++;
	}
}

Checkers::Checkers(const char* filename) {
	char letter = 'A';
	char number = '1';
	string position;
	for (int i = 0; i < 8; i++)
	{
		letter = 'A';
		for (int j = 0; j < 8; j++)
		{
			position = "";
			position += letter;
			position += number;
			this->board[i * 8 + j].value = 'e';
			this->board[i * 8 + j].position = position;
			letter++;
		}
		number++;
	}


	string line;
	ifstream in(filename);
	if (!in)
	{
		cout << "Couldn't open the file!" << endl;
		throw CheckersException();
	}

	char color;

	while (getline(in,line))
	{
		if (line.length()>3)
		{
			if (line.substr(0, 5) == "White")
			{
				color = 'w';
			}
			else if (line.substr(0, 5) == "Black") {
				color = 'b';
			}
			else {
				throw CheckersException();
			}
		}
		else {
			if (line[0] == 'M')
			{
				if (line[1] - 'A' < 0 || line[1] - 'A' > 7)
				{
					throw CheckersException();
				}
				else {
					if (line[2] - '1' < 0 || line[2] - '1' > 7)
					{
						throw CheckersException();
					}
					else {
						this->board[(line[2] - '1') * 8 + (line[1] - 'A')].value = color + 1;
					}
				}
			}
			else if(line[0]-'A'<0 || line[0] - 'A'>7)
			{
				throw CheckersException();
			}
			else {
				if (line[1] - '1' < 0 || line[1] - '1' > 7)
				{
					throw CheckersException();
				}
				else {
					this->board[(line[1] - '1')*8+(line[0] - 'A')].value = color;
				}
			}
		}
	}
	this->countSteps();
}
//найти все возможные ходы для фишки
vector<int> Checkers::findTurns(int nodeNumber) {
	vector<int> turns;

	if (nodeNumber < 64 && nodeNumber > -1)
	{	
		if (this->board[nodeNumber].value == 'w' + 1 || this->board[nodeNumber].value == 'b' + 1)
		{	
			int step = nodeNumber;
			while (step + 8 < 64)
			{	
				step += 8;
				if (step % 8 + 1 < 8)
				{
					step += 1;
					if (this->board[step].value == 'e')
					{
						turns.push_back(step);
					}
					else if (this->board[step].value != this->turn && this->board[step].value != this->turn + 1)
					{
						if (step + 8 < 64 && step % 8 + 1 < 8) {
							if (this->board[step + 9].value == 'e')
							{
								continue;
							}
							else {
								break;
							}
						}
					}
				}
			}

			step = nodeNumber;

			while (step + 8 < 64)
			{
				step += 8;
				if (step % 8 - 1 > -1)
				{
					step -= 1;
					if (this->board[step].value == 'e')
					{
						turns.push_back(step);
					}
					else if (this->board[step].value != this->turn && this->board[step].value != this->turn + 1)
					{
						if (step + 8 < 64 && step % 8 - 1 > -1) {
							if (this->board[step + 8 - 1].value == 'e')
							{
								continue;
							}
							else {
								break;
							}
						}
					}
				}
			}

			step = nodeNumber;

			while (step - 8 > -1)
			{
				step -= 8;
				if (step % 8 + 1 < 8)
				{
					step += 1;
					if (this->board[step].value == 'e')
					{
						turns.push_back(step);
					}
					else if (this->board[step].value != this->turn && this->board[step].value != this->turn + 1)
					{
						if (step - 8 > -1 && step % 8 + 1 < 8) {
							if (this->board[step - 7].value == 'e')
							{
								continue;
							}
							else {
								break;
							}
						}
					}
				}
			}

			step = nodeNumber;

			while (step - 8 > -1)
			{
				step -= 8;
				if (step % 8 - 1 > -1)
				{
					step -= 1;
					if (this->board[step].value == 'e')
					{
						turns.push_back(step);
					}
					else if (this->board[step].value != this->turn && this->board[step].value != this->turn + 1)
					{
						if (step - 8 > -1 && step % 8 - 1 > -1) {
							if (this->board[step - 8 - 1].value == 'e')
							{
								continue;
							}
							else {
								break;
							}
						}
					}
				}
			}
			return turns;
		}
		else {
			if (nodeNumber + 8 < 64) {
				if (nodeNumber % 8 + 1 < 8)
				{
					if (this->board[nodeNumber + 9].value == 'e')
					{
						turns.push_back(nodeNumber + 9);
					}
					else if (this->board[nodeNumber + 9].value != this->turn && this->board[nodeNumber + 9].value != this->turn + 1)
					{
						if (nodeNumber + 18 < 64 && nodeNumber % 8 + 2 < 8) {
							if (this->board[nodeNumber + 18].value == 'e')
							{
								turns.push_back(nodeNumber + 18);
							}
						}
					}
				}

				if (nodeNumber % 8 - 1 > -1)
				{
					if (this->board[nodeNumber + 7].value == 'e')
					{
						turns.push_back(nodeNumber + 7);
					}
					else if (this->board[nodeNumber + 7].value != this->turn && this->board[nodeNumber + 7].value != this->turn + 1)
					{
						if (nodeNumber + 14 < 64 && nodeNumber % 8 - 2 > -1) {
							if (this->board[nodeNumber + 14].value == 'e')
							{
								turns.push_back(nodeNumber + 14);
							}
						}
					}
				}
			}

			if (nodeNumber - 8 > -1)
			{
				if (nodeNumber % 8 - 1 > -1) {
					if (this->board[nodeNumber - 9].value == 'e')
					{
						turns.push_back(nodeNumber - 9);
					}
					else if (this->board[nodeNumber - 9].value != this->turn && this->board[nodeNumber - 9].value != this->turn + 1)
					{
						if (nodeNumber - 18 > -1 && nodeNumber % 8 - 2 > -1) {
							if (this->board[nodeNumber - 18].value == 'e')
							{
								turns.push_back(nodeNumber - 18);
							}
						}
					}
				}

				if (nodeNumber % 8 + 1 < 8) {
					if (this->board[nodeNumber - 7].value == 'e')
					{
						turns.push_back(nodeNumber - 7);
					}
					else if (this->board[nodeNumber - 7].value != this->turn && this->board[nodeNumber - 7].value != this->turn + 1)
					{
						if (nodeNumber - 14 > -1 && nodeNumber % 8 + 2 < 8) {
							if (this->board[nodeNumber - 14].value == 'e')
							{
								turns.push_back(nodeNumber - 14);
							}
						}
					}
				}
			}
		}
	}
	return turns;
}
//посчитать кол-во возможных ходов
void Checkers::countSteps() {
	this->blackSteps = 0;
	this->whiteSteps = 0;
	vector<int> steps;
	for (int i = 0; i < 64; i++)
	{
		if (this->board[i].value == 'w' || this->board[i].value == 'w'+1)
		{
			steps = this->findTurns(i);
			this->whiteSteps += steps.size();

		}
		else if (this->board[i].value == 'b' || this->board[i].value == 'b' + 1) 
		{
			steps = this->findTurns(i);
			this->blackSteps += steps.size();
		}
	}
}
//сделать один ход
void Checkers::makeTurn(int source, int dest) {
	vector<int> possibleTurns = this->findTurns(source);

	for (int i = 0; i < possibleTurns.size(); i++)
	{
		if (possibleTurns[i] == dest) {
			if (abs(dest-source)!=9 && abs(dest - source) != 7)
			{
				int offset;
				offset = abs(dest - source) % 7 == 0 ? 7 : 9;
				offset = (dest - source) > 0 ? -offset : offset;
				this->board[dest].value = this->board[source].value;
				this->board[source].value = 'e';
				this->board[dest + offset].value = 'e';
			}
			else
			{
				this->board[dest].value = this->board[source].value;
				this->board[source].value = 'e';
			}
		}
	}
	
	if (this->turn == 'w')
	{
		this->turn = 'b';
	}
	else
	{
		this->turn = 'w';
	}
	
	this->countSteps();
}

//съесть много фишек за раз
void Checkers::takeMultiple(int source, vector<string> &road) {
	vector<int> turns = this->findTurns(source);

	CheckersTile oldBoard[64];

	for (int i = 0; i < 64; i++)
	{
		oldBoard[i] = this->board[i];
	}

	for (int i = 0; i < turns.size(); i++)
	{
			if (abs(turns[i] - source) != 9 && abs(turns[i] - source) != 7 && this->blackSteps != 0)
			{
				int offset;
				offset = abs(turns[i] - source) % 7 == 0 ? 7 : 9;
				offset = (turns[i] - source) > 0 ? -offset : offset;
				if (this->board[turns[i] + offset].value != 'e')
				{
					this->board[turns[i]].value = this->board[source].value;
					this->board[source].value = 'e';
					this->board[turns[i] + offset].value = 'e';
					this->board[turns[i] + offset].value = 'e';
					road.push_back(this->board[turns[i]].position);
					this->countSteps();
					takeMultiple(turns[i], road);
				}
			}
	}
	if (this->blackSteps!=0)
	{
		for (int i = 0; i < 64; i++)
		{
			this->board[i] = oldBoard[i];
		}
		if (road.size()>0)
		{
			road.pop_back();
		}
		return;
	}
	else {
		return;
	}
}


//узнать возможна ли победа
void Checkers::isWin() {
	CheckersTile oldBoard[64];
	
	for (int i = 0; i < 64; i++)
	{
		oldBoard[i] = this->board[i];
	}

	int turnCount = 0;
	vector<int> possibleTurns;
	vector<string> path;

	for (int i = 0; i < 64; i++)
	{
		if (this->board[i].value == turn || this->board[i].value == turn+1)
		{
			path.push_back(this->board[i].position);
			takeMultiple(i, path);
			if (path.size()>0)
			{
				for (int i = 0; i < path.size()-1; i++) {
					cout << path[i] <<"->"<< path[i+1]<< endl;
				}
				return;
			}
			/*possibleTurns = this->findTurns(i);
			for (int j = 0; j < possibleTurns.size(); j++)
			{
	
				this->makeTurn(i, possibleTurns[j]);
				path.push_back(this->board[possibleTurns[j]].position);
				if (this->blackSteps == 0)
				{
					cout << "Win" << endl;
					cout << "from: " << this->board[i].position << " to: " << this->board[possibleTurns[j]].position << endl;
					this->printBoard();
					return;
				}
				else
				{
					for (int i = 0; i < 64; i++)
					{
						this->board[i] = oldBoard[i];
						this->turn = 'w';
					}
				}
				/*else if ((abs(possibleTurns1[j] - i) > 9))
				{
					int currentTile = possibleTurns1[j];
					vector<int> possibleChainTurns1;
					while (true)
					{
						possibleChainTurns1 = this->findTurns(currentTile);
						for (int j = 0; j < possibleChainTurns1.size(); j++)
						{
							if ((abs(possibleChainTurns1[j] - currentTile) > 9))
							{
								this->makeTurn(i, possibleTurns1[j]);
								if (this->blackSteps == 0)
								{
									cout << "from: " << this->board[i].position << " to: " << this->board[possibleTurns1[j]].position << endl;
									cout << "win" << endl;
									this->printBoard();
									return;
								}
								else {
									currentTile = possibleTurns1[j];
								}
							}
						}
					}
					for (int i = 0; i < 64; i++)
					{
						this->board[i] = oldBoard[i];
					}
				}
			}*/
		}
	}

	cout << "loss" << endl;
	return;

	/*while (turnCount<1)
	{
		for (int i = 0; i < 64; i++)
		{
			this->turn = 'w';
			if (this->board[i].value == turn)
			{
				possibleTurns1 = this->findTurns(i);
				for (int j = 0; j < possibleTurns1.size(); j++)
				{
					this->makeTurn(i, possibleTurns1[j]);
					if (this->blackSteps == 0)
					{
						cout << "from: " << this->board[i].position << " to: " << this->board[possibleTurns1[j]].position << endl;
						cout << "win" << endl;
						this->printBoard();
						return;
					}
					else
					{
						bool winInTwo = true;
						this->turn = 'b';
						for (int i = 0; i < 64; i++)
						{
							if (this->board[i].value == turn)
							{
								possibleTurns2 = this->findTurns(i);
								for (int j = 0; j < possibleTurns2.size(); j++)
								{
									this->makeTurn(i, possibleTurns2[j]);
									if (this->whiteSteps == 0)
									{
										winInTwo = false;
									}
									else
									{
										string winningTurn;
										for (int i = 0; i < 64; i++)
										{
											possibleTurns3 = this->findTurns(i);
											for (int j = 0; j < possibleTurns3.size(); j++)
											{
												this->makeTurn(i, possibleTurns3[j]);
												if (this->blackSteps == 0)
												{
													cout << "from: " << this->board[i].position << " to: " << this->board[possibleTurns3[j]].position << endl;
													cout << "win" << endl;
													this->printBoard();
													return;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		turnCount++;
	}*/

}
//вывести поле
void Checkers::printBoard() {
	std::cout << "  A B C D E F G H"<<endl;
	char number = '1';
	for (int i = 0; i < 8; i++)
	{
		std::cout << number << ' ';
		for (int j = 0; j < 8; j++) {
			std::cout << this->board[i * 8 + j].value << ' ';
		}
		std::cout << std::endl;
		number++;
	}
}