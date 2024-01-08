// сделала только для двоичной системы счисления не особо понимаю что за система счисления 2^2...2^5
#include <stdio.h>

// Функция для перевода числа из десятичной системы в двоичную (или другую) с использованием битовых операций
void decimalToBinaryPowerOfTwo(int number, int power) {
    if (number == 0) {
        printf("0");  // Если число равно 0, выводим ноль
        return;
    }

    for (int i = sizeof(int) * 8 - power; i >= 0; i -= power) {
        // Используем битовую операцию сдвига вправо для извлечения блока битов
        int block = (number >> i) & ((1 << power) - 1);
        printf("%d", block);
    }
}

int main() {
    int decimalNumber = 27;  // Пример числа в десятичной системе
    int powerOfTwo = 3;     // Пример основания степени двойки

    printf("Десятичное число %d в двоичной системе с основанием 2^%d: ", decimalNumber, powerOfTwo);
    decimalToBinaryPowerOfTwo(decimalNumber, powerOfTwo);
    printf("\n");

    return 0;
}
