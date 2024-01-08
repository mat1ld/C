#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

// Функция для сложения двух чисел в столбик в заданной системе счисления
// Считается, что оба числа корректны (без ведущих нулей и других ошибок)
char* addInColumn(char* num1, char* num2, int base) {
    // Определение длины строк
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    // Выделение памяти под результат
    char* result = (char*)malloc((len1 + 2) * sizeof(char));  // +2 для результата и символа '\0'
    result[len1 + 1] = '\0';  // Установка нулевого символа на последней позиции

    // Инициализация переменных
    int carry = 0;
    int index = len1;  // Начинаем с конца строк

    while (index > 0) {
        // Вычисление суммы текущих разрядов и переноса
        int sum = (num1[index - 1] - '0') + (num2[index - 1] - '0') + carry;

        // Установка текущего разряда в результат
        result[index] = (sum % base) + '0';

        // Вычисление переноса для следующей итерации
        carry = sum / base;

        index--;
    }

    // Добавление последнего переноса и оставшегося разряда
    int sum = (num1[0] - '0') + (num2[0] - '0') + carry;
    result[0] = (sum % base) + '0';
    result[1] = (sum / base) + '0';

    // Обрезка ведущего нуля, если он не нужен
    if (result[0] == '0') {
        char* trimmedResult = strdup(result + 1);
        free(result);
        return trimmedResult;
    }

    return result;
}

// Основная функция для вычисления суммы чисел в заданной системе счисления
char* sumInBase(int base, int numCount, ...) {
    va_list args;
    va_start(args, numCount);

    char* sum = "0";  // Начальное значение суммы

    // Суммирование всех переданных чисел
    for (int i = 0; i < numCount; i++) {
        char* currentNum = va_arg(args, char*);
        sum = addInColumn(sum, currentNum, base);
    }

    va_end(args);

    return sum;
}

int main() {
    // Пример использования функции
    char* result = sumInBase(10, 3, "123456789012345678901234567890", "987654321098765432109876543210", "111111111111111111111111111111");
    printf("Сумма: %s\n", result);

    // Освобождение выделенной памяти
    free(result);

    return 0;
}
