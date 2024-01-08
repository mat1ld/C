#include <stdio.h>
#include <stdlib.h>

int main() {
    // �������� ����� ��� ������
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Unable to open the input file!\n");
        return 1;
    }

    // �������� ���������� ����� ��� ������
    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Unable to open the temporary file!\n");
        fclose(inputFile);
        return 2;
    }

    // ���������� ������ �� ��������� ����
    int col1, col2, col3;
    while (fscanf(inputFile, "%d %d %d", &col1, &col2, &col3) == 3) {
        fprintf(tempFile, "%d %d %d\n", col2, col3, col1);
    }

    // �������� ������
    fclose(inputFile);
    fclose(tempFile);

    // �������������� ���������� ����� � ������������ ���
    if (rename("temp.txt", "input.txt") != 0) {
        printf("Unable to rename the temporary file!\n");
        return 3;
    }

    printf("File successfully modified!\n");

    return 0;
}