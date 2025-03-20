#include <fstream>
#include <iostream>
using namespace std;

enum PlayerMovement { UP, DOWN, LEFT, RIGHT };

enum Casillas { PARED, PINCHOS, GEMAS, NADA, PLAYER };

struct Player
{
	int score;
	int posPl[2];
	bool isPlaing;
	PlayerMovement movPl;
	Player();
};

Player::Player() {
	score = 0;
	posPl[0] = 1;
	posPl[1] = 1;
	isPlaing = true;
	movPl = UP;
}

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

void initializeBoard(Casillas** board, int X, int Y, int posPl[])
{
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			board[i][j] = NADA;
		}
	}

	for (int i = 0; i < X && i < Y; i++)
	{
		board[0][i] = PARED;
		board[X-1][i] = PARED;


		
	}


	for (int j = 0; j < Y; j++)
	{

		board[j][0] = PARED;
		board[j][Y - 1] = PARED;





	}


	int posibleCas = (X - 2) * (Y - 2);
	int temp = (int)((posibleCas * 0.1)) + 1;
	int n = rand() % temp;
	for (int i = 0; i < n; i++)
	{
		bool ok = false;
		while (!ok)
		{
			int b = rand() % X;
			int m = rand() % Y;
			if (board[b][m] == NADA)
			{
				board[b][m] = PINCHOS;
				ok = true;
			}
		}
	}

	n = rand() % (int)(posibleCas * 0.25) + 1;
	for (int i = 0; i < n; i++)
	{
		bool ok = false;
		while (!ok)
		{
			int b = rand() % X;
			int m = rand() % Y;
			if (board[b][m] == NADA)
			{
				board[b][m] = GEMAS;
				ok = true;
			}
		}
	}

	posPl[0] = rand() % X;
	posPl[1] = rand() % Y;
	while (board[posPl[0]][posPl[1]] == PARED)
	{
		posPl[0] = rand() % X;
		posPl[1] = rand() % Y;
	}
	board[posPl[0]][posPl[1]] = PLAYER;

}

bool checkMovement(int posPl[], PlayerMovement movPl, Casillas** board)
{
	//Detect if movement is valid
	switch (movPl)
	{
	case UP:
		if (board[posPl[0]][posPl[1] - 1] == PARED)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case DOWN:
		if (board[posPl[0]][posPl[1] + 1] == PARED)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case LEFT:
		if (board[posPl[0] - 1][posPl[1]] == PARED)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case RIGHT:
		if (board[posPl[0] + 1][posPl[1]] == PARED)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	}
}

void addScore(int& score)
{
	score++;
}

void setPosition(int posPl[], PlayerMovement &movPl)
{
	char move;
	bool okKey = false;
	cin >> move;
	while (!okKey)
	{
		switch (move)
		{
		case 'w':
		case 'W':
			movPl = UP;
			okKey = true;
			break;
		case 's':
		case 'S':
			movPl = DOWN;
			okKey = true;
			break;
		case 'a':
		case 'A':
			movPl = LEFT;
			okKey = true;
			break;
		case 'd':
		case 'D':
			movPl = RIGHT;
			okKey = true;
			break;
		}
	}
}

bool existGem(int posPl[], PlayerMovement movPl, Casillas** board)
{
	switch (movPl)
	{
	case UP:
		if (board[posPl[0]][posPl[1] - 1] == GEMAS)
		{

			return true;
		}
		else
		{
			return false;
		}
		break;
	case DOWN:
		if (board[posPl[0]][posPl[1] + 1] == GEMAS)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case LEFT:
		if (board[posPl[0] - 1][posPl[1]] == GEMAS)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case RIGHT:
		if (board[posPl[0] + 1][posPl[1]] == GEMAS)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	}
}

bool existPincho(int posPl[], PlayerMovement movPl, Casillas** board)
{
	switch (movPl)
	{
	case UP:
		if (board[posPl[0]][posPl[1] - 1] == PINCHOS)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case DOWN:
		if (board[posPl[0]][posPl[1] + 1] == PINCHOS)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case LEFT:
		if (board[posPl[0] - 1][posPl[1]] == PINCHOS)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case RIGHT:
		if (board[posPl[0] + 1][posPl[1]] == PINCHOS)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	}
}

void movePlayer(int posPl[], Casillas** board, PlayerMovement movPl)
{
	switch (movPl)
	{
	case UP:
		board[posPl[0]][posPl[1]] = NADA;
		posPl[1] -= 1;
		board[posPl[0]][posPl[1]] = PLAYER;
		break;
	case DOWN:
		board[posPl[0]][posPl[1]] = NADA;
		posPl[1] += 1;
		board[posPl[0]][posPl[1]] = PLAYER;
		break;
	case LEFT:
		board[posPl[0]][posPl[1]] = NADA;
		posPl[0] -= 1;
		board[posPl[0]][posPl[1]] = PLAYER;
		break;
	case RIGHT:
		board[posPl[0]][posPl[1]] = NADA;
		posPl[0] += 1;
		board[posPl[0]][posPl[1]] = PLAYER;
		break;
	}
}

void gameOver(int score)
{
	system("cls");
	cout << endl << "----GAME OVER----" << endl << "TOTAL SCORE: " << score << endl;
}

void printBoard(int x, int y, Casillas** board)
{
	system("cls");

	cout << "P->Pinchos		 X->Player		G->Gemas" << endl;

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (board[j][i] == PARED) {
				cout << "#";

			}
			if (board[j][i] == NADA)
			{
				cout << " ";
			}
			else if (board[j][i] == GEMAS)
			{
				cout << "G";
			}
			else if (board[j][i] == PINCHOS)
			{
				cout << "P";
			}
			else if (board[j][i] == PLAYER)
			{
				cout << "X";
			}
		}
		cout << endl;
	}

	cout << endl << "W A S D - > Move" << endl << endl << "Enter your action: ";
}

void destroyBoard(Casillas** board, int x)
{
	for (int i = 0; i < x; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}

bool ExistGemas(Casillas** board, int X, int Y) {
	int count_gemas = 0;
	for (int i = 0; i < X; i++) {

		for (int j = 0; j < X; j++) {
			if (board[i][j] == GEMAS)
				count_gemas++;
		}

	}
	if (count_gemas > 0) {
		return true;
	}
	else
		return false;

}

int main()
{
	srand(time(NULL));
	bool lose = false;
	int x, y;
	Player player;

	readFile(x, y);
	Casillas** board = new Casillas * [x];
	for (int i = 0; i < x; i++)
	{
		board[i] = new Casillas[y];
	}
	initializeBoard(board, x, y, player.posPl);
	
	
	while (player.isPlaing)
	{
		printBoard(x, y, board);
		setPosition(player.posPl, player.movPl);
		if (existGem(player.posPl, player.movPl, board)) {
			addScore(player.score);
		}
		if (existPincho(player.posPl, player.movPl, board)){
			player.isPlaing = false;
		}
		if (!ExistGemas(board, x, y)) {
			player.isPlaing = false;
		}
		// if hay pared no me muevo
		if (checkMovement(player.posPl, player.movPl, board)) {
			movePlayer(player.posPl, board, player.movPl);
		}
		
	}

	gameOver(player.score);

	destroyBoard(board, x);
	//checkMovement(player.posPl, player.movPl);
}

