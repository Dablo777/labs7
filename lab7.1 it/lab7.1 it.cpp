#include <iostream>
#include <iomanip>
#include <time.h>


void Create(int** t, const int rowCount, const int colCount, const int Low, const int High);
void Print(int** t, const  int rowCount, const int colCount);
void Sort(int** t, const int rowCount, const int colCount);
void Change(int** t, const int row1, const int row2, const int colCount);
void Calc(int** t, const int rowCount, const int colCount, int& S, int& k);

int main() {

	srand((unsigned)time(NULL));

	int Low = -17;
	int Hight = 14;
	int rowCount = 8;
	int colCount = 5;

	int** t = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		t[i] = new int[colCount];

	Create(t, rowCount, colCount, Low, Hight);
	Print(t, rowCount, colCount);
	Sort(t, rowCount, colCount);
	Print(t, rowCount, colCount);

	int S = 0;
	int k = 0;
	Calc(t, rowCount, colCount, S, k);

	std::cout << "Sum: " << S << std::endl;
	std::cout << "Count: " << k << std::endl;
	Print(t, rowCount, colCount);
	for (int i = 0; i < rowCount; i++)
		delete[] t[i];

	delete[] t;
	return 0;
}

void Create(int** t, const int rowCount, const int colCount, const int Low,
	const int High)
{
	for (int i = 0; i < rowCount; i++)
		for (int j = 0; j < colCount; j++)
			t[i][j] = Low + rand() % (High - Low + 1);
}

void Print(int** t, const int rowCount, const int colCount)
{
	std::cout << std::endl;
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
			std::cout << " " << std::setw(4) << t[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool isFirstColumn(int** t, int j) {
	return t[j][0] > t[j + 1][0];
}


bool isSecondColumn(int** t, int j) {
	return t[j][0] == t[j + 1][0] &&
		(t[j][1] > t[j + 1][1]);
}

bool isThirdColumn(int** t, int j) {
	return t[j][0] == t[j + 1][0] &&
		t[j][1] == t[j + 1][1] &&
		t[j][2] > t[j + 1][2];
}

void Sort(int** t, const int rowCount, const int colCount) {
	for (int i = 0; i < rowCount - 1; i++)
		for (int j = 0; j < rowCount - i - 1; j++)
			if (
				isFirstColumn(t, j)
				||
				isSecondColumn(t, j)
				||
				isThirdColumn(t, j)
				)
			{
				Change(t, j, j + 1, colCount);
			}
}

void Change(int** t, const int row1, const int row2, const int colCount)
{
	int tmp;
	for (int j = 0; j < colCount; j++)
	{
		tmp = t[row1][j];
		t[row1][j] = t[row2][j];
		t[row2][j] = tmp;
	}
}

void Calc(int** t, const int rowCount, const int colCount, int& S, int& k)
{
	S = 0;
	k = 0;
	for (int i = 0; i < rowCount; i++)
		for (int j = 0; j < colCount; j++)
			if (t[i][j] < 0 && !(t[i][j] % 4 == 0))
			{
				S += t[i][j];
				k++;
				t[i][j] = 0;
			}
}

