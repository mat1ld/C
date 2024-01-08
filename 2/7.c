#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

// ������� ��� �������� ���� ����� � ������� � �������� ������� ���������
// ���������, ��� ��� ����� ��������� (��� ������� ����� � ������ ������)
char* addInColumn(char* num1, char* num2, int base) {
    // ����������� ����� �����
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    // ��������� ������ ��� ���������
    char* result = (char*)malloc((len1 + 2) * sizeof(char));  // +2 ��� ���������� � ������� '\0'
    result[len1 + 1] = '\0';  // ��������� �������� ������� �� ��������� �������

    // ������������� ����������
    int carry = 0;
    int index = len1;  // �������� � ����� �����

    while (index > 0) {
        // ���������� ����� ������� �������� � ��������
        int sum = (num1[index - 1] - '0') + (num2[index - 1] - '0') + carry;

        // ��������� �������� ������� � ���������
        result[index] = (sum % base) + '0';

        // ���������� �������� ��� ��������� ��������
        carry = sum / base;

        index--;
    }

    // ���������� ���������� �������� � ����������� �������
    int sum = (num1[0] - '0') + (num2[0] - '0') + carry;
    result[0] = (sum % base) + '0';
    result[1] = (sum / base) + '0';

    // ������� �������� ����, ���� �� �� �����
    if (result[0] == '0') {
        char* trimmedResult = strdup(result + 1);
        free(result);
        return trimmedResult;
    }

    return result;
}

// �������� ������� ��� ���������� ����� ����� � �������� ������� ���������
char* sumInBase(int base, int numCount, ...) {
    va_list args;
    va_start(args, numCount);

    char* sum = "0";  // ��������� �������� �����

    // ������������ ���� ���������� �����
    for (int i = 0; i < numCount; i++) {
        char* currentNum = va_arg(args, char*);
        sum = addInColumn(sum, currentNum, base);
    }

    va_end(args);

    return sum;
}

int main() {
    // ������ ������������� �������
    char* result = sumInBase(10, 3, "123456789012345678901234567890", "987654321098765432109876543210", "111111111111111111111111111111");
    printf("�����: %s\n", result);

    // ������������ ���������� ������
    free(result);

    return 0;
}
