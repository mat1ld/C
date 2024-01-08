#include <stdio.h>
#include <stdarg.h>

// ������� ��� �����������, ����� �� ���������� ����� �������� ������������� � ������� ���������
// � ���������� ����������
int hasFiniteRepresentation(int base, int numCount, ...) {
    va_list args;
    va_start(args, numCount);

    // ���������� ��� �������� ����� ��������� � ���������� ����
    int decimalBaseSum = 0;

    // ������������ ��������� ��� ������������ ������������� � ��������
    for (int i = 0; i < numCount; i++) {
        decimalBaseSum += va_arg(args, int);
    }

    va_end(args);

    // ��������, �������� �� ����� ��������� �������� ������
    while (decimalBaseSum > 1) {
        if (decimalBaseSum % base != 0) {
            return 0;  // ���� �� ������� ������, �� �� ����� �������� �������������
        }
        decimalBaseSum /= base;
    }

    return 1;  // ���� ����� �� 1, �� ����� �������� �������������
}

int main() {
    // ������ ������������� �������
    int result1 = hasFiniteRepresentation(2, 3, 10, 8, 4);  // 10(2) + 8(2) + 4(2) = 22(2)
    int result2 = hasFiniteRepresentation(3, 2, 9, 3);        // 9(3) + 3(3) = 12(3)

    printf("��������� 1: %s\n", result1 ? "��" : "���");
    printf("��������� 2: %s\n", result2 ? "��" : "���");

    return 0;
}