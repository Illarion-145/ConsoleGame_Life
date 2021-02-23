#include <iostream>
using namespace std;

int** createMatrix(int n);
void inputRandomMatrix(int** matrix, int n);
void inputMatrix(int** matrix, int n);
bool isCorrectMatrix(int** matrix, int n);
void copyMatrix(int** matrix, int** matrix_new, int n);
int checkNeighborsCell(int** matrix, int n, int posI, int posJ);
void outputMatrix(int** matrix, int n);
bool checkCondition1(int** matrix, int n); // На поле нет ни одной "живой" клетки, true - нету, false - есть хотя бы одно живая
bool checkCondition2(int** matrix, int** matrix_last, int n); // Симуляция зациклилась - true, иначе false

int main() {

    setlocale(LC_ALL, "Russian");
    int n, counter = 0;
    bool isRandomInput;

    cout << "0 - мертвая клетка\n1 - живая клетка\n";
    cout << "Введите размер поля (n * n): ";
    cin >> n;
    cout << "Ввести первую симуляцию рандомно? (1 - Да, 0 - Нет) - ";
    cin >> isRandomInput;

    int **matrix = createMatrix(n),
        **matrix_last = createMatrix(n),
        **matrix_new = createMatrix(n);

    if (isRandomInput) 
        inputRandomMatrix(matrix, n);
    else {
        inputMatrix(matrix, n);
        while (!isCorrectMatrix(matrix, n)) {
            cout << "Матрица некорректна: " << endl;
            cout << "Отсутствуют некоторые элементы или они не принадлежат к интервалу целых чисел - [0, 1]." << endl;
            cout << "Повторите ввод матрицы..." << endl;
            inputMatrix(matrix, n);
        }
    }
    cout << endl << "Начало симуляций!" << endl << endl;
    outputMatrix(matrix, n);
    counter++;

    while (checkCondition1(matrix, n) == false && checkCondition2(matrix, matrix_last, n) == false) {
        copyMatrix(matrix, matrix_last, n);
        copyMatrix(matrix, matrix_new, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((matrix[i][j] == 0) && (checkNeighborsCell(matrix, n, i, j) == 3))
                    matrix_new[i][j] = 1;
                if ((matrix[i][j] == 1) && ((checkNeighborsCell(matrix, n, i, j) < 2) || (checkNeighborsCell(matrix, n, i, j) > 3)))
                    matrix_new[i][j] = 0;
            }
        }
        copyMatrix(matrix_new, matrix, n);
        if (checkCondition2(matrix, matrix_last, n))
            break;
        outputMatrix(matrix, n);
        counter++;
    }

    cout << "Игра закончилась! ";  
    if (checkCondition1(matrix, n))
        cout << "На поле нет ни одной \"живой\" клетки...";
    else if (checkCondition2(matrix, matrix_last, n))
        cout << "Симуляция зациклилась...";
    cout << endl << "Всего симуляций: " << counter << endl;

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
void inputMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> matrix[i][j];
}
bool isCorrectMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!(matrix[i][j] == 0 || matrix[i][j] == 1))
                return false;
    return true;
}
void copyMatrix(int** matrix, int** matrix_new, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix_new[i][j] = matrix[i][j];
}
int checkNeighborsCell(int** matrix, int n, int posI, int posJ) {
    int counter = 0,
        startPosJ = (posJ - 1 >= 0) ? posJ - 1 : posJ,
        endPosJ = (posJ + 1 < n) ? posJ + 1 : posJ,
        startPosI = (posI - 1 >= 0) ? posI - 1 : posI,
        endPosI = (posI + 1 < n) ? posI + 1 : posI;

    for (int i = startPosI; i <= endPosI; i++) {
        for (int j = startPosJ; j <= endPosJ; j++) {
            if (i == posI && j == posJ)
                continue;
            else if (matrix[i][j] == 1)
                counter++;
        }
    }
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
}
