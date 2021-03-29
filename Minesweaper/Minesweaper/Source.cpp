#include <iostream>
#include <time.h>
using namespace std;

const int grid_size = 10;
char grid_visible[grid_size][grid_size];
char grid_mines[grid_size][grid_size];

bool hitMine = false;

void Generte_Visible_Grid(int size) {
	system("CLS");

	cout << "/ | ";

	for (int i = 0; i < size; i++)
	{
		cout << i << " | ";
	}

	for (int i = 0; i < size; i++)
	{
		cout << endl << i << " | ";
		for (int j = 0; j < size; j++)
		{
			cout << grid_visible[i][j] << " | ";
		}
	}
	cout << endl;
}

void Calculate_Number_In_Cell(int i, int j) {
	if (i >= 0 && j >= 0 && i < grid_size && j < grid_size && grid_mines[i][j] != 'X') {
		(int)grid_mines[i][j]++;
	}
}

void GenerateMines(int count){
	int counter = 0;
	int i = 0;
	int j = 0;
	while (counter < count)
	{
		

		i = rand() % grid_size;
		j = rand() % grid_size;
		if (grid_mines[i][j] != 'X') {
			grid_mines[i][j] = 'X';
			Calculate_Number_In_Cell(i + 1, j);
			Calculate_Number_In_Cell(i + 1, j + 1);
			Calculate_Number_In_Cell(i + 1, j - 1);
			Calculate_Number_In_Cell(i - 1, j);
			Calculate_Number_In_Cell(i - 1, j + 1);
			Calculate_Number_In_Cell(i - 1, j - 1);
			Calculate_Number_In_Cell(i, j + 1);
			Calculate_Number_In_Cell(i, j - 1);
			counter++;
		}
	}
}

int RevealCell(int i, int j) {
	if (i < 0 || i >= grid_size || j < 0 || j >= grid_size) {
		return -1;
	}
	else {
		if (grid_mines[i][j] == 'X') {
			grid_visible[i][j] = 'X';
			hitMine = true;
		}
		else
		{
			if (grid_mines[i][j] == '0' && grid_visible[i][j] != 'F' && grid_visible[i][j] != '0') {
				grid_visible[i][j] = grid_mines[i][j];
				RevealCell(i + 1, j);		//right cell
				RevealCell(i + 1, j + 1);	//right down cell
				RevealCell(i + 1, j - 1);	//right up cell
				RevealCell(i - 1, j);		//left cell
				RevealCell(i - 1, j + 1);	//left down cell
				RevealCell(i - 1, j - 1);	//left up cell
				RevealCell(i, j + 1);		//down cell
				RevealCell(i, j - 1);		//up cell
			}
			else
			{
				grid_visible[i][j] = grid_mines[i][j];
			}
		}
	}
	return 0;
}

int PlaceFlag(int i, int j) {
	if (i < 0 && i > grid_size && j < 0 && j > grid_size) {
		return -1;
	}if (grid_visible[i][j] == 0) {
		grid_visible[i][j] = 'F';
	}
	return 0;
}

int SafelyInput(char inputText) {
	int number = 0;
	bool isStarted = true;
	do {
		cout << "Enter " << inputText << ": ";
		cin >> number;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		isStarted = false;
	} while (isStarted);

	return number;
}

void RevealMines(int size) {

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (grid_mines[i][j] == 'X') {
				grid_visible[i][j] = 'X';
			}
		}
	}

}

bool isWin(int size) {
	bool win = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (grid_mines[i][j] != 'X') {
				if (grid_visible[i][j] == grid_mines[i][j]) {
					win = true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return win;

}

int main() {
	
	srand(time(NULL));

	int x = 0;
	int y = 0;
	char action;
	bool Win = false;
	
	cout << "Loading..." << endl;

	//generate visible and mines grids
	for (int i = 0; i < grid_size; i++)
	{
		for (int j = 0; j < grid_size; j++)
		{
			grid_mines[i][j] = '0';
			grid_visible[i][j] = 0;
		}
	}
	GenerateMines(grid_size);

	do {
		Generte_Visible_Grid(grid_size);
		cout << "Enter coordinates and action (R to reveal and F to place flag):" << endl;
		do {
			x = SafelyInput('X');
		} while (x < 0 || x >= grid_size);
		do {
			y = SafelyInput('Y');
		} while (y < 0 || y >= grid_size);
		do {
			cout << "Enter action:";
			cin >> action;
		} while (!(action == 'R' || action == 'F'));

		if (action == 'R') {
			RevealCell(y, x);
		}
		else
		{
			if (action == 'F') {
				PlaceFlag(y, x);
			}
		}

		Win = isWin(grid_size);

	} while (!hitMine && !Win);
	RevealMines(grid_size);
	Generte_Visible_Grid(grid_size);

	if (Win) {

		cout << endl << "You win!" << endl;
	}
	else {
		cout << "You lose!" << endl;
	}

	return 0;
}