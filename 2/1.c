#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// ������� ��� �������� ����� ������
char* countLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    // ��������� ������ ��� ����� ������
    char* result = (char*)malloc((length + 1) * sizeof(char));

    // ����������� ������ � ���������� ������
    for (int i = 0; i <= length; i++) {
        result[i] = str[i];
    }

    return result;
}

// ������� ��� ��������������� ������
char* reverseString(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    // ��������� ������ ��� ����� ������
    char* result = (char*)malloc((length + 1) * sizeof(char));

    // ������ �������� � �������� �������
    for (int i = 0; i < length; i++) {
        result[i] = str[length - i - 1];
    }
    result[length] = '\0';

    return result;
}

// ������� ��� �������������� ������� ��������� ������� � ������� �������
char* toUpperCaseOdd(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    // ��������� ������ ��� ����� ������
    char* result = (char*)malloc((length + 1) * sizeof(char));

    // �������������� ������� ��������� ������� � ������� �������
    for (int i = 0; i < length; i++) {
        if (i % 2 != 0) {
            result[i] = (char)toupper(str[i]);
        }
        else {
            result[i] = str[i];
        }
    }
    result[length] = '\0';

    return result;
}

// ������� ��� ������������ ����� � ��������������� �������
char* concatenateRandom(const char* str1, const char* str2, unsigned int seed) {
    int length1 = 0;
    while (str1[length1] != '\0') {
        length1++;
    }

    int length2 = 0;
    while (str2[length2] != '\0') {
        length2++;
    }

    // ��������� ������ ��� ����� ������
    char* result = (char*)malloc((length1 + length2 + 1) * sizeof(char));

    // ������������� ���������� ��������������� �����
    srand(seed);

    // ������������ ����� � ��������������� �������
    int i = 0, j = 0;
    while (i < length1 && j < length2) {
        if (rand() % 2 == 0) {
            result[i + j] = str1[i++];
        }
        else {
            result[i + j] = str2[j++];
        }
    }

    // ���������� ���������� ��������, ���� ����
    while (i < length1) {
        result[i + j] = str1[i++];
    }
    while (j < length2) {
        result[i + j] = str2[j++];
    }

    result[length1 + length2] = '\0';

    return result;
}

// ������� ��� ������������ ������, ���������� ��� ������
void freeString(char* str) {
    free(str);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Not enough arguments.\n");
        return 1;
    }

    char* flag = argv[1];
    char* inputString = argv[2];

    char* resultString;

    if (strcmp(flag, "-l") == 0) {
        resultString = countLength(inputString);
    }
    else if (strcmp(flag, "-r") == 0) {
        resultString = reverseString(inputString);
    }
    else if (strcmp(flag, "-u") == 0) {
        resultString = toUpperCaseOdd(inputString);
    }
    else if (strcmp(flag, "-c") == 0) {
        if (argc < 4) {
            printf("Not enough arguments for flag -c.\n");
            return 1;
        }

        unsigned int seed;
        if (sscanf(argv[3], "%u", &seed) != 1) {
            printf("Invalid seed value.\n");
            return 1;
        }

        // ����� ������� concatenateRandom � ����� �������� � seed
        resultString = concatenateRandom(inputString, argv[4], seed);
    }
    else {
        printf("Invalid flag.\n");
        return 1;
    }

    // ����� ����������
    printf("Result: %s\n", resultString);

    // ������������ ������
    freeString(resultString);

    return 0;
}