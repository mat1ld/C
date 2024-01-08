#include <stdio.h>
#include <stdarg.h>  // ��� ������ � ���������� ������ ����������
#include <stdlib.h>  // ��� ������ � �������
#include <string.h>

// ������� ��� ������ ��������� � �����
void findSubstringInFile(const char* substring, const char* filePath) {
    FILE* file = fopen(filePath, "r");  // �������� ����� ��� ������
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    int lineNumber = 0;

    // ������ ����� �� �������
    while ((read = getline(&line, &len, file)) != -1) {
        lineNumber++;

        char* position = line;
        int charNumber = 0;

        // ����� ��������� ��������� � ������
        while ((position = strstr(position, substring)) != NULL) {
            // ����� ���������� � ��������� ���������
            printf("File: %s, Line: %d, Character: %d\n", filePath, lineNumber, charNumber + 1);
            // ����������� ������� ��� ������ ���������� ���������
            position++;
            charNumber = (int)(position - line);
        }
    }

    free(line);
    fclose(file);
}

// ������ ������������� �������
int main() {
    findSubstringInFile("example", "file1.txt");
    findSubstringInFile("substring", "file2.txt");

    return 0;
}

