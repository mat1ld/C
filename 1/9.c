#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <math.h>

void findMaxModulo(int base);

int main() {
    findMaxModulo(0);  // �������� � ������ ������������� ����� �� ������ � ������� ��������� 0, ����� ��������� ���������

    return 0;
}

void findMaxModulo(int base) {
    int maxAbs = 0;
    char number[100];

    if (base == 0) {
        printf("������� ������� ��������� (�� 2 �� 36): ");
        scanf("%d", &base);

        if (base <= 2 || base >= 36) {
            printf("�������� ������� ���������!\n");
            return;
        }
    }

    printf("������� ����� � ������� ��������� %d (��� ��������� ������� 'Stop'):\n", base);

    while (1) {
        scanf("%s", number);

        if (strcmp(number, "Stop") == 0) {
            break;
        }
        else {
            char* endptr;
            long int value = strtol(number, &endptr, base);

            if (*endptr != '\0') {
                printf("����� %s �� ������������� ������� ��������� � ���������� %d\n", number, base);
            }
            else {
                printf("����� %s ������������� ������� ��������� � ���������� %d\n", number, base);

                int absValue = abs(value);
                if (absValue > maxAbs) {
                    maxAbs = absValue;
                }
            }
        }
    }

    printf("������������ ����� �� ������: %d\n", maxAbs);
    printf("������������ ����� �� ������ 9: %d\n", maxAbs % 9);
    printf("������������ ����� �� ������ 18: %d\n", maxAbs % 18);
    printf("������������ ����� �� ������ 27: %d\n", maxAbs % 27);
    printf("������������ ����� �� ������ 36: %d\n", maxAbs % 36);
}