#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����������� ���� ��������� String
typedef struct {
    char* data;  // ��������� �� ������������ ������ ��������
    int length;  // ���������� �������� (����� ������)
} String;

// ������� �������� ���������� ���� String �� ������ �������� ���� char *
String createString(const char* initial) {
    String newString;

    // ��������� ������ ��� ����������� ���������� ������
    newString.data = strdup(initial);

    if (newString.data == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // ���������� ����� ������
    newString.length = strlen(initial);

    return newString;
}

// ������� �������� ����������� ����������� ���������� ���� String
void deleteStringContent(String* str) {
    free(str->data);  // ������������ ���������� ������������ ������
    str->data = NULL;  // ��������� ��������� � NULL
    str->length = 0;   // ��������� ����� � 0
}

// ������� ��������� ������� ����� ����� ������������ ���� String
int compareStrings(const String* str1, const String* str2) {
    // ������� ���������� �� �����
    if (str1->length < str2->length) return -1;
    if (str1->length > str2->length) return 1;

    // ���� ����� �����, ���������� ���������������� ����������
    return strcmp(str1->data, str2->data);
}

// ������� ��������� ��������������� ����� ����� ������������ ���� String
int areStringsEqual(const String* str1, const String* str2) {
    return (compareStrings(str1, str2) == 0);
}

// ������� ����������� ����������� ���������� ���� String � ������������ ���������
void copyString(String* destination, const String* source) {
    // ������������ �������� �����������
    deleteStringContent(destination);

    // ��������� ����� ������ � ����������� ������
    destination->data = strdup(source->data);

    if (destination->data == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // ��������� ����� �����
    destination->length = source->length;
}

// ������� ����������� ����������� ���������� ���� String � ����� ���������
String copyStringToNew(const String* source) {
    return createString(source->data);
}

// ������� ������������ � ����������� ������� ���������� ���� String ����������� �������
String concatenateStrings(const String* str1, const String* str2) {
    String result;

    // ��������� ������ ��� ����������������� ������
    result.data = (char*)malloc(str1->length + str2->length + 1);

    if (result.data == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // ����������� ������ � ��������� ����� �����
    strcpy(result.data, str1->data);
    strcat(result.data, str2->data);
    result.length = str1->length + str2->length;

    return result;
}

int main() {
    // ������ �������������
    String s1 = createString("Hello");
    String s2 = createString("World");

    printf("Comparison result: %d\n", compareStrings(&s1, &s2));
    printf("Equality result: %d\n", areStringsEqual(&s1, &s2));

    String s3;
    copyString(&s3, &s1);

    String s4 = copyStringToNew(&s2);

    String s5 = concatenateStrings(&s1, &s2);

    // ������������ ��������
    deleteStringContent(&s1);
    deleteStringContent(&s2);
    deleteStringContent(&s3);
    deleteStringContent(&s4);
    deleteStringContent(&s5);

    return 0;
}
