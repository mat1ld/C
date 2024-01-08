#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <math.h>

void findMaxModulo(int base);

int main() {
    findMaxModulo(0);  // Ќачинаем с поиска максимального числа по модулю в системе счислени€ 0, чтобы запросить основание

    return 0;
}

void findMaxModulo(int base) {
    int maxAbs = 0;
    char number[100];

    if (base == 0) {
        printf("¬ведите систему счислени€ (от 2 до 36): ");
        scanf("%d", &base);

        if (base <= 2 || base >= 36) {
            printf("Ќеверна€ система счислени€!\n");
            return;
        }
    }

    printf("¬ведите числа в системе счислени€ %d (дл€ остановки введите 'Stop'):\n", base);

    while (1) {
        scanf("%s", number);

        if (strcmp(number, "Stop") == 0) {
            break;
        }
        else {
            char* endptr;
            long int value = strtol(number, &endptr, base);

            if (*endptr != '\0') {
                printf("„исло %s не соответствует системе счислени€ с основанием %d\n", number, base);
            }
            else {
                printf("„исло %s соответствует системе счислени€ с основанием %d\n", number, base);

                int absValue = abs(value);
                if (absValue > maxAbs) {
                    maxAbs = absValue;
                }
            }
        }
    }

    printf("ћаксимальное число по модулю: %d\n", maxAbs);
    printf("ћаксимальное число по модулю 9: %d\n", maxAbs % 9);
    printf("ћаксимальное число по модулю 18: %d\n", maxAbs % 18);
    printf("ћаксимальное число по модулю 27: %d\n", maxAbs % 27);
    printf("ћаксимальное число по модулю 36: %d\n", maxAbs % 36);
}