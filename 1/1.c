#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[]) {
    int i = 0, pr_flag;
    int value = 0, acc = 0;
    char str[1000];

    // �������� ���������� ����������
    if (argc != 3) {
        printf("Invalid arguments count!");
        return 1;
    }

    // ����������� �������� ����� � �������� ���������� 'value'
    if (sscanf(argv[2], "%u", &value) != 1 || value == 0) {
        printf("Invalid ");
        return 2;
    }

    // ��������� ��������� ������
    if (strcmp(argv[1], "-h") == 0 || (strcmp(argv[1], "/h") == 0)) {
        acc = value;

        // ����� ����� � ����� 'value' �� 100
        while (acc <= 100) {
            printf("%d\n", acc);
            acc += value;
        }
    }
    else if (strcmp(argv[1], "-p") == 0 || (strcmp(argv[1], "/p") == 0)) {
        // �������� �� �������� ���������� �����
        if (value == 1) {
            printf("Not prime neither composite\n");
        }
        else if (value == 2) {
            printf("Prime\n");
        }
        else if ((value & 1) == 0) {
            printf("Composite\n");
        }
        else {
            // �������� �� �������� ����� ��������
            pr_flag = 1;
            for (i = 3; i <= (int)sqrt(value); i += 2)
                if (value % i == 0) {
                    pr_flag = 0;
                    break;
                }

            printf(pr_flag == 0 ? "Composite" : "Prime");
        }
    }
    else if (strcmp(argv[1], "-s") == 0 || (strcmp(argv[1], "/s") == 0)) {
        // ����� ���� ����� � ������
        snprintf(str, sizeof str, "%d", value);
        while (i <= strlen(str)) {
            printf("%c ", str[i]);
            i++;
        }
    }
    else if (strcmp(argv[1], "-e") == 0 || (strcmp(argv[1], "/e") == 0)) {
        // ����� ������� �������� ��� ����� �� 10
        int st;
        if (value <= 10) {
            for (i = 1; i <= 10; i++) {
                for (st = 1; st <= value; st++) {
                    printf("%.0f ", pow(i, st));
                }
                printf("\n");
            }
        }
    }
    else if (strcmp(argv[1], "-a") == 0 || (strcmp(argv[1], "/a") == 0)) {
        // ����� ����� ����������� ����� �� ���������� ��������
        int pr = 0;
        for (i = 1; i <= value; i++) {
            pr += i;
        }
        printf("%d", pr);
    }
    else if (strcmp(argv[1], "-f") == 0 || (strcmp(argv[1], "/f") == 0)) {
        // ����� ���������� ���������� ��������
        int num;
        num = tgamma(value + 1);
        printf("%d", num);
    }
    return 0;
}