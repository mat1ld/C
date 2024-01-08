#include <stdio.h>
#include <stdlib.h>

int main() {
    // Открытие файла для чтения
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Unable to open the input file!\n");
        return 1;
    }

    // Открытие временного файла для записи
    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Unable to open the temporary file!\n");
        fclose(inputFile);
        return 2;
    }

    // Перезапись данных во временный файл
    int col1, col2, col3;
    while (fscanf(inputFile, "%d %d %d", &col1, &col2, &col3) == 3) {
        fprintf(tempFile, "%d %d %d\n", col2, col3, col1);
    }

    // Закрытие файлов
    fclose(inputFile);
    fclose(tempFile);

    // Переименование временного файла в оригинальное имя
    if (rename("temp.txt", "input.txt") != 0) {
        printf("Unable to rename the temporary file!\n");
        return 3;
    }

    printf("File successfully modified!\n");

    return 0;
}