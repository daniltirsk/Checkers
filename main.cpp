// checkers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Checkers.h"

using namespace std;

int main()
{
    Checkers f("board.txt");
    f.printBoard();
    f.isWin();
    f.printBoard();
}
