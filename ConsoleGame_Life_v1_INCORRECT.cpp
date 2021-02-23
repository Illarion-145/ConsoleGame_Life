#include <iostream>
using namespace std;

int** createMatrix(int n);

void inputRandomMatrix(int** matrix, int n);

void copyMatrix(int** matrix, int** matrix_new, int n);

int checkNeighborsCell(int** matrix, int n, int posI, int posJ);

void outputMatrix(int** matrix, int n);

bool checkCondition1(int** matrix, int n); // На поле нет ни одной "живой" клетки, true - нету, false - есть хотя бы одно живая

bool checkCondition2(int** matrix, int** matrix_last, int n); // Симуляция зациклилась - true, иначе false

int main() {

    setlocale(LC_ALL, "Russian");

    int counter = 0;

    cout << "0 - мертвая клетка\n1 - живая клетка\n";
	
    int n;
    cout << "Введите размер поля (n * n): ";
    cin >> n;

    int** matrix = createMatrix(n);
    inputRandomMatrix(matrix, n);

    int** matrix_last = createMatrix(n);

    while (checkCondition1(matrix, n) == false && checkCondition2(matrix, matrix_last, n) == false ) {
        outputMatrix(matrix, n);
        counter++;
        copyMatrix(matrix, matrix_last, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((matrix[i][j] == 0) && (checkNeighborsCell(matrix, n, i, j) == 3))
                    matrix[i][j] = 1;
                if ((matrix[i][j] == 1) && ((checkNeighborsCell(matrix, n, i, j) < 2) || (checkNeighborsCell(matrix, n, i, j) > 3)))
                    matrix[i][j] = 0;
            }
        }
    }

    cout << "Игра закончилась! Всего симуляций: " << counter << endl;

    return 0;
}
int** createMatrix(int n) {
    int** m = new int* [n];
    for (int i = 0; i < n; i++)
        m[i] = new int[n];
    return m;
}

void inputRandomMatrix(int** matrix, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = rand() % 2;
}

void copyMatrix(int** matrix, int** matrix_new, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix_new[i][j] = matrix[i][j];
}

int checkNeighborsCell(int** matrix, int n, int posI, int posJ) {
    int counter = 0;

    int startPosJ = (posJ - 1 >= 0) ? posJ - 1 : posJ;
    int endPosJ = (posJ + 1 < n) ? posJ + 1 : posJ;

    if (posI - 1 >= 0) {                         // 3 верхних соседа
        for (int i = startPosJ; i <= endPosJ; i++)
            if (matrix[posI - 1][i] == 1)
                counter++;
    }
    if (posI + 1 < n) {                          // 3 нижних соседа
        for (int i = posJ - 1; i <= posJ + 1; i++)
            if (matrix[posI + 1][i] == 1)
                counter++;
    }
    if ((posJ - 1 >= 0) && (matrix[posI][posJ - 1] == 1))
        counter++;
    if ((posJ + 1 < n) && (matrix[posI][posJ + 1] == 1))
        counter++;

    return counter;
}

void outputMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
}

bool checkCondition1(int** matrix, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == 1)
                return false;
    return true;
}

bool checkCondition2(int** matrix, int** matrix_last, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] != matrix_last[i][j])
                return false;
    return true;
