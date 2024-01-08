#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

void inputNumber(int* number);
void inputSizeOfMatrix(int* n, int* m);
int** alocateMemory(const int n, const int m);
void generateMatrix(int** matrix, const int n, const int m);
void outputMatrix(const int** matrix, const int n, const int m);
void multiplicationMatrix(const int** A, const int row1, const int col1, const int** B, const int row2, const int col2, int** C);
void minor(int** src, int** dest, int row, int col, int order);
int determinantOfMatrix(int** matrix, int rows);
void freeMemmory(int** matrix, int rows);
void block1();
void block2(const int number);
void check1(int cols, int rows);
int check2(int cols, int rows);

int main() {
	int number = 0;
	setlocale(LC_ALL, "rus");
	printf("Программа предоставляет пользователю возможность работать с матрицами.\n");
	printf("Для продолжения работы необходимо выбрать один из трех следующих пунктов:\n");
	printf("1. Функция генерации матрицы произвольных размеров (число строк/столбцов: [1..10])\n с произвольными значениями (диапазон значений элементов : [-100..100]).\n");
	printf("2. Функция умножения двух матриц.\n");
	printf("3. Функция вычисления определителя матрицы.\n");
	inputNumber(&number);
	if (number == 1) {
		block1();
	}
	else if (number == 2 || number == 3){
		block2(number);
	}
	else {
		printf("Вы ввели некорретное значение. Программа завершает свою работу!");
	}
	return 0;
}

void inputSizeOfMatrix(int* n, int* m) {
	printf("Введите количество строк и столбцов в матрице:\n");
	while (1) {
		scanf("%d %d", n, m);
		if ((*n >= 1 && *n <= 10) && (*m >= 1 && *m <= 10)) {
			break;
		}
		else {
			printf("Будьте внимательны число строк/столбцов: [1..10].\n");
		}
		
	}
}
void inputNumber(int* number) {
	scanf("%d", number);
}
int** alocateMemory(const int n, const int m) {
	int** matrix = (int**)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		matrix[i] = (int*)malloc(m * sizeof(int));
	}
	return matrix;
}
void generateMatrix(int** matrix, const int n, const int m) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) {
			matrix[i][j] = (rand() % 201) - 100;
		}
	}
}
void outputMatrix(const int** matrix, const int n, const int m) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}
void multiplicationMatrix(const int** A, const int row1, const int col1, const int** B, const int row2, const int col2, int** C) {
	int sum = 0;
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			C[i][j] = 0;
			for (int k = 0; k < col1; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}
void minor(int** src, int** dest, int row, int col, int order) {
	int colCount = 0, rowCount = 0;
	for (int i = 0; i < order; i++) {
		if (i != row) {
			colCount = 0;
			for (int j = 0; j < order; j++) {
				if (j != col) {
					dest[rowCount][colCount] = src[i][j];
					colCount++;
				}
			}
			rowCount++;
		}
	}
}
int determinantOfMatrix(int** matrix, int cols) {
	int result = 0;
	if (cols == 1) {
		return matrix[0][0];
	}
	int** temp = (int**)malloc(cols * sizeof(int*));
	for (int i = 0; i < cols; i++) {
		temp[i] = (int*)malloc(cols * sizeof(int));
	}
	int sign = 1;
	for (int f = 0; f < cols; f++) {
		minor(matrix, temp, 0, f, cols);
		result = result + sign * matrix[0][f] * determinantOfMatrix(temp, cols - 1);
		sign = -sign;
	}
	for (int i = 0; i < cols; i++) {
		free(temp[i]);
	}
	temp = NULL;
	return result;
}
void freeMemmory(int** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		free(matrix[i]);
	}
	matrix = NULL;
}
void block1() {
	int** matrix;
	int rows, cols;
	printf("\nУкажите необходимое количество строк и столбцов в матрице:\n");
	scanf("%d %d", &cols, &rows);
	matrix = alocateMemory(rows, cols);
	generateMatrix(matrix, rows, cols);
	outputMatrix(matrix, rows, cols);
	for (int i = 0; i < rows; i++) {
		free(matrix[i]);
	}
	matrix = NULL;
}
void block2(const int number) {
	int rows1, cols1, rows2, cols2;
	int** A, ** B;
	inputSizeOfMatrix(&rows1, &cols1);
	inputSizeOfMatrix(&rows2, &cols2);
	A = alocateMemory(rows1, cols1);
	B = alocateMemory(rows2, cols2);
	generateMatrix(A, rows1, cols1);
	generateMatrix(B, rows2, cols2);
	outputMatrix(A, rows1, cols1);
	outputMatrix(B, rows2, cols2);
	if (number == 2) {
		check1(cols1, rows2);
		int** C;
		C = alocateMemory(rows1, cols2);
		multiplicationMatrix(A, rows1, cols1, B, rows2, cols2, C);
		outputMatrix(C, rows1, cols2);
		freeMemmory(A, rows1);
		freeMemmory(B, rows2);
		freeMemmory(C, rows1);
	}
	else {
		if (check2(rows1, cols1)) {
			int det = determinantOfMatrix(A, rows1);
			freeMemmory(A, rows1);
			printf("Определитель матрицы первой матрицы равен: %d.\n", det);
		} 
		if (check2(rows2, cols2)) {
			int det = determinantOfMatrix(B, rows2);
			printf("Определитель матрицы первой матрицы равен: %d.\n", det);
			freeMemmory(B, rows2);
		}
	}


}
void check1(int cols, int rows) {
	if (cols != rows) {
		printf("Умножение матриц невозможно. Число столбцов первой матрицы не равно числу строк во второй матрице\n");
		exit(1);
	}
}
int check2(int rows, int cols) {
	if (rows != cols) {
		printf("Вычисление определителя матрицы невозможно.\n");
		return 0;
	}
	else { 
		return 1; 
	}
}
