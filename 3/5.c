#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��������� ��� ������������� ��������
typedef struct {
    unsigned int id;
    char firstName[50];
    char lastName[50];
    char group[10];
    unsigned char* examScores;
} Student;

// ������� ��� ��������� ��������� �� �� id
int compareStudentsById(const void* a, const void* b) {
    return ((const Student*)a)->id - ((const Student*)b)->id;
}

// ������� ��� ��������� ��������� �� �������
int compareStudentsByLastName(const void* a, const void* b) {
    return strcmp(((const Student*)a)->lastName, ((const Student*)b)->lastName);
}

// ������� ��� ��������� ��������� �� �����
int compareStudentsByFirstName(const void* a, const void* b) {
    return strcmp(((const Student*)a)->firstName, ((const Student*)b)->firstName);
}

// ������� ��� ��������� ��������� �� ������
int compareStudentsByGroup(const void* a, const void* b) {
    return strcmp(((const Student*)a)->group, ((const Student*)b)->group);
}

// ������� ��� �������� ������� ������ ��������
double calculateAverageScore(const Student* student, int examsCount) {
    double sum = 0.0;
    for (int i = 0; i < examsCount; ++i) {
        sum += student->examScores[i];
    }
    return (sum / examsCount);
}

int main(int argc, char* argv[]) {
    // �������� ������� ���������� ��������� ������
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // �������� �����
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // ���������� ��������� �� �����
    int studentsCount;
    fscanf(file, "%d", &studentsCount);

    Student* students = (Student*)malloc(studentsCount * sizeof(Student));
    if (students == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < studentsCount; ++i) {
        fscanf(file, "%u %s %s %s", &students[i].id, students[i].firstName,
            students[i].lastName, students[i].group);

        students[i].examScores = (unsigned char*)malloc(5 * sizeof(unsigned char));
        if (students[i].examScores == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            fclose(file);
            free(students);
            return EXIT_FAILURE;
        }

        for (int j = 0; j < 5; ++j) {
            fscanf(file, "%hhu", &students[i].examScores[j]);
        }
    }

    fclose(file);

    // �������������� � �������������
    int option;
    printf("Choose an option:\n");
    printf("1. Search student by id\n");
    printf("2. Search student by last name\n");
    printf("3. Search student by first name\n");
    printf("4. Search student by group\n");
    scanf("%d", &option);

    qsort(students, studentsCount, sizeof(Student), compareStudentsById);

    switch (option) {
    case 1: {
        unsigned int searchId;
        printf("Enter student id: ");
        scanf("%u", &searchId);

        Student key = { .id = searchId };
        Student* result = bsearch(&key, students, studentsCount, sizeof(Student), compareStudentsById);

        if (result != NULL) {
            // �������� ����� ��� ������
            FILE* traceFile = fopen("trace.txt", "w");
            if (traceFile == NULL) {
                fprintf(stderr, "Error opening trace file\n");
                free(students);
                return EXIT_FAILURE;
            }

            // ����� ���������� � �������������� ����
            fprintf(traceFile, "Student found by id:\n");
            fprintf(traceFile, "ID: %u\n", result->id);
            fprintf(traceFile, "Full Name: %s %s\n", result->firstName, result->lastName);
            fprintf(traceFile, "Group: %s\n", result->group);
            fprintf(traceFile, "Average Score: %.2f\n", calculateAverageScore(result, 5));

            // �������� ��������������� �����
            fclose(traceFile);
        }
        else {
            printf("Student not found.\n");
        }
        break;
    }


    default:
        printf("Invalid option\n");
    }

    // ������������ ��������
    for (int i = 0; i < studentsCount; ++i) {
        free(students[i].examScores);
    }
    free(students);

    return EXIT_SUCCESS;


}