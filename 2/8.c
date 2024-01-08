#include <stdio.h>
#include <stdarg.h>

// Функция для определения, имеет ли десятичная дробь конечное представление в системе счисления
// с переданным основанием
int hasFiniteRepresentation(int base, int numCount, ...) {
    va_list args;
    va_start(args, numCount);

    // Переменная для хранения суммы оснований в десятичном виде
    int decimalBaseSum = 0;

    // Суммирование оснований для последующего использования в проверке
    for (int i = 0; i < numCount; i++) {
        decimalBaseSum += va_arg(args, int);
    }

    va_end(args);

    // Проверка, является ли сумма оснований степенью двойки
    while (decimalBaseSum > 1) {
        if (decimalBaseSum % base != 0) {
            return 0;  // Если не делится нацело, то не имеет конечное представление
        }
        decimalBaseSum /= base;
    }

    return 1;  // Если дошли до 1, то имеет конечное представление
}

int main() {
    // Пример использования функции
    int result1 = hasFiniteRepresentation(2, 3, 10, 8, 4);  // 10(2) + 8(2) + 4(2) = 22(2)
    int result2 = hasFiniteRepresentation(3, 2, 9, 3);        // 9(3) + 3(3) = 12(3)

    printf("Результат 1: %s\n", result1 ? "Да" : "Нет");
    printf("Результат 2: %s\n", result2 ? "Да" : "Нет");

    return 0;
}