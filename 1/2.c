#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
    // Проверка на количество аргументов
    if (argc < 4) {
        printf("Insufficient number of arguments!\n");
        return 1;
    }

    // Обработка флага -q (квадратное уравнение)
    if (argv[1][0] == '-' && argv[1][1] == 'q') {
        // Извлечение коэффициентов из аргументов
        double a = atof(argv[2]);
        double b = atof(argv[3]);
        double c = atof(argv[4]);

        // Вычисление дискриминанта
        double discriminant = b * b - 4 * a * c;

        // Вывод решений квадратного уравнения
        if (discriminant > 0) {
            double root1 = (-b + sqrt(discriminant)) / (2 * a);
            double root2 = (-b - sqrt(discriminant)) / (2 * a);
            printf("Root 1: %lf\n", root1);
            printf("Root 2: %lf\n", root2);
        }
        else if (discriminant == 0) {
            double root = -b / (2 * a);
            printf("Double root: %lf\n", root);
        }
        else {
            printf("No real roots\n");
        }
    }

    // Обработка флага -m (определение кратности)
    else if (argv[1][0] == '-' && argv[1][1] == 'm') {
        // Извлечение двух ненулевых целых чисел
        int num1 = atoi(argv[2]);
        int num2 = atoi(argv[3]);

        // Проверка кратности
        if (num1 % num2 == 0) {
            printf("%d is a multiple of %d\n", num1, num2);
        }
        else {
            printf("%d is not a multiple of %d\n", num1, num2);
        }
    }

    // Обработка флага -t (прямоугольный треугольник)
    else if (argv[1][0] == '-' && argv[1][1] == 't') {
        // Извлечение трех ненулевых значений
        double side1 = atof(argv[2]);
        double side2 = atof(argv[3]);
        double side3 = atof(argv[4]);

        // Проверка на возможность образования прямоугольного треугольника
        if (side1 * side1 + side2 * side2 == side3 * side3 || side1 * side1 + side3 * side3 == side2 * side2 || side2 * side2 + side3 * side3 == side1 * side1) {
            printf("These values can form a right-angled triangle.\n");
        }
        else {
            printf("These values cannot form a right-angled triangle.\n");
        }
    }

    return 0;
}