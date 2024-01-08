#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ������� ����������� ������� ��������� ��� �����
int detectBase(const char* number) {
    int base = 10; // �� ��������� �������, ��� ����� � ���������� �������

    // ���������, ���� ����� ���������� � "0x", �� ��� ����������������� �������
    if (strncmp(number, "0x", 2) == 0) {
        base = 16;
    }
    // ���������, ���� ����� ���������� � "0b", �� ��� �������� �������
    else if (strncmp(number, "0b", 2) == 0) {
        base = 2;
    }
    // ���������, ���� ����� ���������� � "0", �� ��� ������������ �������
    else if (number[0] == '0') {
        base = 8;
    }

    return base;
}

// ������� �������������� ����� �� ������ � ���������� �����
long long convertToDecimal(const char* number, int base) {
    return strtoll(number, NULL, base);
}

int main() {
    FILE* inputFile, * outputFile;
    char buffer[100];
    long long decimalNumber;

    // �������� �������� ����� ��� ������
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // �������� ��������� ����� ��� ������
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 2;
    }

    // ���������� ����� �� ����� ���������
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        // ������� ��������� ������� ��� ������� �������� ������ � ����� ������
        size_t length = strlen(buffer);
        while (length > 0 && (buffer[length - 1] == ' ' || buffer[length - 1] == '\n' || buffer[length - 1] == '\r')) {
            buffer[--length] = '\0';
        }

        // ����������� ������� ��������� ��� �����
        int base = detectBase(buffer);

        // �������������� ����� � ���������� �������
        decimalNumber = convertToDecimal(buffer, base);

        // ������ ���������� � �������� ����
        fprintf(outputFile, "Number: %s, Base: %d, Decimal: %lld\n", buffer, base, decimalNumber);
    }

    // �������� ������
    fclose(inputFile);
    fclose(outputFile);

    printf("Conversion completed successfully.\n");

    return 0;
}