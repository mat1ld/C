#include <stdio.h>
#include <stdarg.h>  // Для работы с переменным числом аргументов
#include <stdlib.h>  // Для работы с файлами
#include <string.h>

// Функция для поиска подстроки в файле
void findSubstringInFile(const char* substring, const char* filePath) {
    FILE* file = fopen(filePath, "r");  // Открытие файла для чтения
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    int lineNumber = 0;

    // Чтение файла по строкам
    while ((read = getline(&line, &len, file)) != -1) {
        lineNumber++;

        char* position = line;
        int charNumber = 0;

        // Поиск вхождений подстроки в строке
        while ((position = strstr(position, substring)) != NULL) {
            // Вывод информации о найденном вхождении
            printf("File: %s, Line: %d, Character: %d\n", filePath, lineNumber, charNumber + 1);
            // Перемещение позиции для поиска следующего вхождения
            position++;
            charNumber = (int)(position - line);
        }
    }

    free(line);
    fclose(file);
}

// Пример использования функции
int main() {
    findSubstringInFile("example", "file1.txt");
    findSubstringInFile("substring", "file2.txt");

    return 0;
}

