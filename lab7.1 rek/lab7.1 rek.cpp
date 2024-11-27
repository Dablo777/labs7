#include <iostream>
#include <iomanip>
#include <time.h>

void CreateRecursive(int** t, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0);
void Print(int** t, const int rowCount, const int colCount);
void SortRecursive(int** t, const int rowCount, const int colCount, int i = 0, int j = 0);
void Change(int** t, const int row1, const int row2, const int colCount);
void CalcRecursive(int** t, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0);

bool isFirstColumn(int** t, int j);
bool isSecondColumn(int** t, int j);
bool isThirdColumn(int** t, int j);

int main() {
    srand((unsigned)time(NULL));

    int Low = -17;
    int High = 14;
    int rowCount = 8;
    int colCount = 5;

    int** t = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        t[i] = new int[colCount];

    CreateRecursive(t, rowCount, colCount, Low, High);
    Print(t, rowCount, colCount);

    SortRecursive(t, rowCount, colCount);
    Print(t, rowCount, colCount);

    int S = 0;
    int k = 0;
    CalcRecursive(t, rowCount, colCount, S, k);

    std::cout << "Sum: " << S << std::endl;
    std::cout << "Count: " << k << std::endl;

    Print(t, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] t[i];
    delete[] t;

    return 0;
}

// Рекурсивне створення
void CreateRecursive(int** t, const int rowCount, const int colCount, const int Low, const int High, int i, int j) {
    if (i >= rowCount) return;
    if (j >= colCount) {
        CreateRecursive(t, rowCount, colCount, Low, High, i + 1, 0);
        return;
    }
    t[i][j] = Low + rand() % (High - Low + 1);
    CreateRecursive(t, rowCount, colCount, Low, High, i, j + 1);
}

// Друк таблиці
void Print(int** t, const int rowCount, const int colCount) {
    std::cout << std::endl;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++)
            std::cout << " " << std::setw(4) << t[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Рекурсивне сортування
void SortRecursive(int** t, const int rowCount, const int colCount, int i, int j) {
    if (i >= rowCount - 1) return;
    if (j >= rowCount - i - 1) {
        SortRecursive(t, rowCount, colCount, i + 1, 0);
        return;
    }
    if (isFirstColumn(t, j) || isSecondColumn(t, j) || isThirdColumn(t, j)) {
        Change(t, j, j + 1, colCount);
    }
    SortRecursive(t, rowCount, colCount, i, j + 1);
}

// Зміна рядків
void Change(int** t, const int row1, const int row2, const int colCount) {
    for (int j = 0; j < colCount; j++) {
        int tmp = t[row1][j];
        t[row1][j] = t[row2][j];
        t[row2][j] = tmp;
    }
}

// Рекурсивний підрахунок
void CalcRecursive(int** t, const int rowCount, const int colCount, int& S, int& k, int i, int j) {
    if (i >= rowCount) return;
    if (j >= colCount) {
        CalcRecursive(t, rowCount, colCount, S, k, i + 1, 0);
        return;
    }
    if (t[i][j] < 0 && !(t[i][j] % 4 == 0)) {
        S += t[i][j];
        k++;
        t[i][j] = 0;
    }
    CalcRecursive(t, rowCount, colCount, S, k, i, j + 1);
}

bool isFirstColumn(int** t, int j) {
    return t[j][0] > t[j + 1][0];
}

bool isSecondColumn(int** t, int j) {
    return t[j][0] == t[j + 1][0] && t[j][1] > t[j + 1][1];
}

bool isThirdColumn(int** t, int j) {
    return t[j][0] == t[j + 1][0] && t[j][1] == t[j + 1][1] && t[j][2] > t[j + 1][2];
}
