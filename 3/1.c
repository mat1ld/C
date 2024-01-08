// ������� ������ ��� �������� ������� ��������� �� ����� ������� ��� �� ������� ��������� 2^2...2^5
#include <stdio.h>

// ������� ��� �������� ����� �� ���������� ������� � �������� (��� ������) � �������������� ������� ��������
void decimalToBinaryPowerOfTwo(int number, int power) {
    if (number == 0) {
        printf("0");  // ���� ����� ����� 0, ������� ����
        return;
    }

    for (int i = sizeof(int) * 8 - power; i >= 0; i -= power) {
        // ���������� ������� �������� ������ ������ ��� ���������� ����� �����
        int block = (number >> i) & ((1 << power) - 1);
        printf("%d", block);
    }
}

int main() {
    int decimalNumber = 27;  // ������ ����� � ���������� �������
    int powerOfTwo = 3;     // ������ ��������� ������� ������

    printf("���������� ����� %d � �������� ������� � ���������� 2^%d: ", decimalNumber, powerOfTwo);
    decimalToBinaryPowerOfTwo(decimalNumber, powerOfTwo);
    printf("\n");

    return 0;
}
