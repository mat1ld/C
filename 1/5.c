#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* outputFile; // Указатель на выходной файл
    char ch; // Переменная для считывания символов из файлов

    // Проверка количества аргументов командной строки
    if (argc < 4) {
        printf("Invalid number of arguments!\n");
        return 1;
    }

    // Открытие выходного файла для записи
    outputFile = fopen(argv[argc - 1], "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        return 2;
    }

    // Обработка входных файлов
    for (int i = 2; i < argc - 1; i++) {
        FILE* inputFile; // Указатель на текущий входной файл

        // Открытие текущего входного файла для чтения
        inputFile = fopen(argv[i], "r");
        if (inputFile == NULL) {
            perror("Error opening input file");
            fclose(outputFile);
            return 3;
        }

        // Считывание и запись символов из текущего входного файла в выходной файл
        while ((ch = fgetc(inputFile)) != EOF) {
            fputc(ch, outputFile);
        }

        // Закрытие текущего входного файла
        fclose(inputFile);
    }

    // Закрытие выходного файла
    fclose(outputFile);

    printf("Files merged successfully.\n");

    return 0;
}