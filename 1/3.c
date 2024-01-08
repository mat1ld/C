#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// �������, ������� ������������ ���������� ��������� �������� ���� � ������
void countLetters(const char* str, int* letterCount) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            char letter = tolower(str[i]);
            letterCount[letter - 'a']++;
        }
    }
}

// �������, ������� �������� ������� �� ���������� ������� ��� ������� �� ASCII-����
void replaceNonAlphanumeric(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum(str[i])) {
            sprintf(str + i, "%d", (int)str[i]); // ������ �� ASCII-���
        }
    }
}

int main(int argc, char* argv[]) {
    // �������� �� ���������� ����������
    if (argc < 3) {
        printf("Insufficient number of arguments!\n");
        return 1;
    }

    // ����������� �����
    char flag = argv[1][1];

    // �������� �������� �����
    FILE* inputFile = fopen(argv[2], "r");
    if (inputFile == NULL) {
        printf("Unable to open the input file!\n");
        return 2;
    }

    // ����������� ��������� �����
    char* outputFileName;
    if (argc >= 4) {
        outputFileName = argv[3];
    }
    else {
        // ��������� ����� ��������� �����
        outputFileName = malloc(strlen(argv[2]) + 5); // 5 ��� "out_" � ������������ ������� '\0'
        strcpy(outputFileName, "out_");
        strcat(outputFileName, argv[2]);
    }

    // �������� ��������� �����
    FILE* outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Unable to open the output file!\n");
        fclose(inputFile);
        free(outputFileName);
        return 3;
    }

    // ��������� ����� -d (���������� ����)
    if (flag == 'd') {
        int ch;
        while ((ch = fgetc(inputFile)) != EOF) {
            if (!isdigit(ch)) {
                fputc(ch, outputFile);
            }
        }
    }

    // ��������� ����� -i (������� ��������� �������� ����)
    else if (flag == 'i') {
        char line[1000];
        while (fgets(line, sizeof(line), inputFile) != NULL) {
            int letterCount[26] = { 0 }; // ��� ������ ����� ��������
            countLetters(line, letterCount);

            fprintf(outputFile, "Letters count per line:\n");
            for (int i = 0; i < 26; i++) {
                fprintf(outputFile, "%c: %d\n", 'a' + i, letterCount[i]);
            }
        }
    }

    // ��������� ����� -s (������� ��������� ��������, �������� �� ����, ���� � �������)
    else if (flag == 's') {
        char line[1000];
        while (fgets(line, sizeof(line), inputFile) != NULL) {
            int specialCharCount = 0;
            for (int i = 0; line[i] != '\0'; i++) {
                if (!isalnum(line[i]) && !isspace(line[i])) {
                    specialCharCount++;
                }
            }
            fprintf(outputFile, "Special characters count per line: %d\n", specialCharCount);
        }
    }

    // ��������� ����� -a (������ �������� �� ���������� ������� ��� ������� �� ASCII-����)
    else if (flag == 'a') {
        char line[1000];
        while (fgets(line, sizeof(line), inputFile) != NULL) {
            replaceNonAlphanumeric(line);
            fputs(line, outputFile);
        }
    }

    // ��������� ����� -f (������ �������� � ������ ������ ������� �� ��������, � ����� � ������ ����� �� ASCII-����)
    else if (flag == 'f') {
        char word[100];
        int wordCount = 0;

        while (fscanf(inputFile, "%s", word) == 1) {
            if (++wordCount % 2 == 0) {
                for (int i = 0; word[i] != '\0'; i++) {
                    word[i] = tolower(word[i]); // ������ �� �������� �����
                }
            }

            if (wordCount % 5 == 0) {
                replaceNonAlphanumeric(word); // ������ �� ASCII-����
            }

            fprintf(outputFile, "%s ", word);
        }
    }

    // �������� ������ � ������������ ������
    fclose(inputFile);
    fclose(outputFile);
    free(outputFileName);

    return 0;
}