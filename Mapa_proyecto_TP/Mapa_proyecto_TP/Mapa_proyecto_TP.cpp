#include <fstream>
#include <iostream>
#include <vector>
//#include "PlayerMov.h"
//#include ""
using namespace std;

enum PlayerMovement { UP, DOWN, LEFT, RIGHT };

enum Casillas { PARED, PINCHOS, GEMAS, NADA };

struct Player
{
	int score;
	vector<int> posPl{ 0,0 };
};

void readFile(int& x, int& y)
{
	ifstream file("config.txt");
	if (file.is_open())
	{
		int i = 0, n; //Es fa servir aquesta varaible i per fer que les variables nomes agafin els dos primers numeros com a coordenades igualment que n'hi hagi més dins el fitxer.
			while (file >> n)
		{
			if (i < 1)
			{
				x = n;
				i++;
			}
			else if (i < 2)
			{
				y = n;
				i++;
			}
		}
	}
	else
	{
		cout << "ERROR" << endl;
	}
	file.close();
}

void initializeBoard(Casillas** board, int x, int y,vector<int> posPl)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			board[i][j] = NADA;
		}
	}
	
	for (int i = 0; i < x && i < y; i++)
	{
		board[i][0] = PARED;
		board[0][i] = PARED;
		board[i][y] = PARED;
		board[x][i] = PARED;
	}
	
	int posibleCas = (x - 2) * (y - 2);
	int n = rand() % (int)(posibleCas * 0.1) + 1;
	for (int i = 0; i < n; i++)
	{
		bool ok = false;
		while (!ok)
		{
			int b = rand() % x;
			int m = rand() % y;
			if (board[b][m] == NADA)
			{
				board[b][m] = PINCHOS;
				ok = true;
			}
		}
	}

	int n = rand() % (int)(posibleCas * 0.25) + 1;
	for (int i = 0; i < n; i++)
	{
		bool ok = false;
		while (!ok)
		{
			int b = rand() % x;
			int m = rand() % y;
			if (board[b][m] == NADA)
			{
				board[b][m] = GEMAS;
				ok = true;
			}
		}
	}

	posPl[0] = rand() % x;
	posPl[1] = rand() % y;//segir

}

/*bool checkMovement(int coorPl[], PlayerMovement movPl)
{
	//Detect if movement is valid
	if (coorPl[0] == 0 && movPl == LEFT || coorPl[1] == 0 && movPl == UP)
	{
		return false;
	}
}*/

int main()
{
	srand(time(NULL));
	int x, y;
	Player player;
	readFile(x, y);
	Casillas** board = new Casillas * [x];
	for (int i = 0; i < x; i++)
	{
		board[i] = new Casillas[y];
	}

	initializeBoard(board, x, y, player.posPl);
}

