#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* outputFile; // ��������� �� �������� ����
    char ch; // ���������� ��� ���������� �������� �� ������

    // �������� ���������� ���������� ��������� ������
    if (argc < 4) {
        printf("Invalid number of arguments!\n");
        return 1;
    }

    // �������� ��������� ����� ��� ������
    outputFile = fopen(argv[argc - 1], "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        return 2;
    }

    // ��������� ������� ������
    for (int i = 2; i < argc - 1; i++) {
        FILE* inputFile; // ��������� �� ������� ������� ����

        // �������� �������� �������� ����� ��� ������
        inputFile = fopen(argv[i], "r");
        if (inputFile == NULL) {
            perror("Error opening input file");
            fclose(outputFile);
            return 3;
        }

        // ���������� � ������ �������� �� �������� �������� ����� � �������� ����
        while ((ch = fgetc(inputFile)) != EOF) {
            fputc(ch, outputFile);
        }

        // �������� �������� �������� �����
        fclose(inputFile);
    }

    // �������� ��������� �����
    fclose(outputFile);

    printf("Files merged successfully.\n");

    return 0;
}