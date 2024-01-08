#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Функция определения системы счисления для числа
int detectBase(const char* number) {
    int base = 10; // По умолчанию считаем, что число в десятичной системе

    // Проверяем, если число начинается с "0x", то это шестнадцатеричная система
    if (strncmp(number, "0x", 2) == 0) {
        base = 16;
    }
    // Проверяем, если число начинается с "0b", то это двоичная система
    else if (strncmp(number, "0b", 2) == 0) {
        base = 2;
    }
    // Проверяем, если число начинается с "0", то это восьмеричная система
    else if (number[0] == '0') {
        base = 8;
    }

    return base;
}

// Функция преобразования числа из строки в десятичное число
long long convertToDecimal(const char* number, int base) {
    return strtoll(number, NULL, base);
}

int main() {
    FILE* inputFile, * outputFile;
    char buffer[100];
    long long decimalNumber;

    // Открытие входного файла для чтения
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Открытие выходного файла для записи
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 2;
    }

    // Считывание чисел из файла построчно
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        // Убираем возможные пробелы или символы переноса строки в конце строки
        size_t length = strlen(buffer);
        while (length > 0 && (buffer[length - 1] == ' ' || buffer[length - 1] == '\n' || buffer[length - 1] == '\r')) {
            buffer[--length] = '\0';
        }

        // Определение системы счисления для числа
        int base = detectBase(buffer);

        // Преобразование числа в десятичную систему
        decimalNumber = convertToDecimal(buffer, base);

        // Запись результата в выходной файл
        fprintf(outputFile, "Number: %s, Base: %d, Decimal: %lld\n", buffer, base, decimalNumber);
    }

    // Закрытие файлов
    fclose(inputFile);
    fclose(outputFile);

    printf("Conversion completed successfully.\n");

    return 0;
}