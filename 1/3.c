#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Функция, которая подсчитывает количество вхождений символов букв в строке
void countLetters(const char* str, int* letterCount) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            char letter = tolower(str[i]);
            letterCount[letter - 'a']++;
        }
    }
}

// Функция, которая заменяет символы не являющиеся буквами или цифрами на ASCII-коды
void replaceNonAlphanumeric(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum(str[i])) {
            sprintf(str + i, "%d", (int)str[i]); // Замена на ASCII-код
        }
    }
}

int main(int argc, char* argv[]) {
    // Проверка на количество аргументов
    if (argc < 3) {
        printf("Insufficient number of arguments!\n");
        return 1;
    }

    // Определение флага
    char flag = argv[1][1];

    // Открытие входного файла
    FILE* inputFile = fopen(argv[2], "r");
    if (inputFile == NULL) {
        printf("Unable to open the input file!\n");
        return 2;
    }

    // Определение выходного файла
    char* outputFileName;
    if (argc >= 4) {
        outputFileName = argv[3];
    }
    else {
        // Генерация имени выходного файла
        outputFileName = malloc(strlen(argv[2]) + 5); // 5 для "out_" и завершающего символа '\0'
        strcpy(outputFileName, "out_");
        strcat(outputFileName, argv[2]);
    }

    // Открытие выходного файла
    FILE* outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Unable to open the output file!\n");
        fclose(inputFile);
        free(outputFileName);
        return 3;
    }

    // Обработка флага -d (исключение цифр)
    if (flag == 'd') {
        int ch;
        while ((ch = fgetc(inputFile)) != EOF) {
            if (!isdigit(ch)) {
                fputc(ch, outputFile);
            }
        }
    }

    // Обработка флага -i (подсчет вхождений символов букв)
    else if (flag == 'i') {
        char line[1000];
        while (fgets(line, sizeof(line), inputFile) != NULL) {
            int letterCount[26] = { 0 }; // Для каждой буквы алфавита
            countLetters(line, letterCount);

            fprintf(outputFile, "Letters count per line:\n");
            for (int i = 0; i < 26; i++) {
                fprintf(outputFile, "%c: %d\n", 'a' + i, letterCount[i]);
            }
        }
    }

    // Обработка флага -s (подсчет вхождений символов, отличных от цифр, букв и пробела)
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

    // Обработка флага -a (замена символов не являющихся буквами или цифрами на ASCII-коды)
    else if (flag == 'a') {
        char line[1000];
        while (fgets(line, sizeof(line), inputFile) != NULL) {
            replaceNonAlphanumeric(line);
            fputs(line, outputFile);
        }
    }

    // Обработка флага -f (замена символов в каждой второй лексеме на строчные, а также в каждой пятой на ASCII-коды)
    else if (flag == 'f') {
        char word[100];
        int wordCount = 0;

        while (fscanf(inputFile, "%s", word) == 1) {
            if (++wordCount % 2 == 0) {
                for (int i = 0; word[i] != '\0'; i++) {
                    word[i] = tolower(word[i]); // Замена на строчные буквы
                }
            }

            if (wordCount % 5 == 0) {
                replaceNonAlphanumeric(word); // Замена на ASCII-коды
            }

            fprintf(outputFile, "%s ", word);
        }
    }

    // Закрытие файлов и освобождение памяти
    fclose(inputFile);
    fclose(outputFile);
    free(outputFileName);

    return 0;
}