
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void block1(const int* pArray, const int size);
void block2(const int* pArray, const int size);
void block3(const int* pArray, const int size);
void block4(const int* pArray, const int size);
void block5(const int* pArray, const int size);
void calculateCountElemetsOnOddPos(const int size, int* outSize);
int countEvenNumbers(const int* pArray, const int size);
void readDataFromFile(int** massive, const char *path, int size);
int sizeArray(const char* path);



int main() {
	int size = 0;
	int marker = 1; // Необходим для выхода из программы, маркер обнуляется при условии, что ввели корректные значения
	int* pArray = NULL;
	char str[] = "input.txt";
	size = sizeArray(str);
	readDataFromFile(&pArray, str, size);
	while (marker) 
	{
		char symbol;
		scanf("%c", &symbol); // Чтение символа с консоли
		switch (symbol) {
		case 'a':
			block1(pArray, size);
			marker = 0;
			break;
		case 'b':
			block2(pArray, size);
			marker = 0;
			break;
		case 'c':
			block3(pArray, size);
			marker = 0;
			break;
		case 'd':
			block4(pArray, size);
			marker = 0;
			break;
		case 'e':
			block5(pArray, size);
			marker = 0;
			break;
		default:
			printf("Be careful. Please enter symbol: a, b, c, d, e.\n"); 
			break;
		}		
	}
	free(pArray); // Очистка динамической памяти
	return 0;
}

void block1(const int* pArray, const int size) {
	int tempSize;
	int* tArray;
	/*
	for (int i = 0; i < size; i++) {
		printf("%d\ ", pArray[i]);
	}
	printf("\n******\n");
	*/
	calculateCountElemetsOnOddPos(size, &tempSize);
	tArray = (int*)malloc(tempSize * sizeof(int));
	for (int i = 0, j = 0; i < size; i++) {
		if (i % 2 == 1) {
			tArray[j] = pArray[i];
			j++;
		}
	}
	for (int j = 0; j < tempSize; j++) {
		printf("%d ", tArray[j]);
	}
	free(tArray);
}
void block2(const int* pArray, const int size) {
	int tempLength = countEvenNumbers(pArray, size);
	int* tempArray = (int*)malloc(tempLength * sizeof(int));
	for (int i = 0, j = 0; i < size; i++) {
		if (pArray[i] % 2 == 0) {
			tempArray[j] = pArray[i];
			j++;
		}
	}
	for (int i = 0; i < tempLength; i++) {
		printf("%d ", tempArray[i]);
	}
	free(tempArray);
	return;
}
void block3(const int* pArray, const int size) {
	int pos;
	while (1) {
		int distant = 0, maxDistance = 0;;
		printf("Please write index position in array:");
		scanf("%d", &pos);
		if ((pos < 0) || (pos > size)) { // Защита от дурака в случае ввода некорректных данных
			printf("Please write correct position. Between 0 and %d!", size-12);
			continue;
		}
		for (int i = 0; i < size; i++) {
			if (abs(pArray[i] - pArray[pos]) > maxDistance && pos != i) { 
				maxDistance = abs(pArray[i] - pArray[pos]);
				distant = pArray[i];
			}
		}
		printf("Distance element %d for element %d.\n", distant, pArray[pos]);
		return;
	}
}
void block4(const int* pArray, const int size) {
	int pos;
	while (1) {
		int sum = 0;
		printf("Please write index position in array:");
		scanf("%d", &pos);
		if (pos < 0 || pos > size) {
			printf("Please write correct position. Between 0 and %d!", size-1);
			continue;
		}
		for (int i = 0; i < pos; i++) {
			sum += pArray[i];
		}
		printf("Sum elements before %d is %d.\n", pArray[pos], sum);
		return;
	}
}
void block5(const int* pArray, const int size) {
	int pos;
	while (1) {
		int sum = 0;
		printf("Please write index position in array:");
		scanf("%d", &pos);
		if (pos < 0 || pos > size) {
			printf("Please write correct position. Between 0 and %d!", size);
			continue;
		}
		for (int i = 0; i < pos; i++) {
			if (pArray[i] < pArray[pos]) {
				sum += pArray[i];
			}
		}
		printf("Sum elements before %d which smaller than %d is %d.\n", pArray[pos], pArray[pos], sum);
		return;
	}
}
void calculateCountElemetsOnOddPos(const int size, int* outSize) {
	if (size % 2 == 0) {
		*outSize = size / 2;
	}
	else {
		*outSize = size / 2 + 1;
	}
}
int countEvenNumbers(const int* pArray, const int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (pArray[i] % 2 == 0) {
			count++;
		}
	}
	return count;
}
void readDataFromFile(int** massive, const char *path, const int size) {
	FILE* file = fopen(path, "r");
	int i = 0;
	*massive = (int*)malloc(size * sizeof(int));
	while (!feof(file))
	{
		fscanf(file, "%d\n", &(*massive)[i]);
		i++;			
	}
	fclose(file);
}
int sizeArray(const char* path)
{
	int linesCount = 0;
	FILE* file = fopen(path, "r");
	while (!feof(file)) 
	{
		if (fgetc(file) == '\n')
			linesCount++;
	}
	linesCount++;
	fclose(file);
	return linesCount;
}

