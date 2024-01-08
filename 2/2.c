#include <stdio.h>
#include <stdarg.h>  // ƒл€ работы с переменным числом аргументов
#include <math.h>

// 1. ‘ункци€ дл€ вычислени€ среднего геометрического
double calculateGeometricMean(int count, ...) {
    if (count <= 0) {
        printf("Invalid number of arguments for geometric mean calculation.\n");
        return 0.0;
    }

    // »спользуем тип va_list дл€ работы с переменным числом аргументов
    va_list args;
    va_start(args, count);

    double product = 1.0;
    for (int i = 0; i < count; i++) {
        double num = va_arg(args, double);
        // ѕроверка на отрицательное число, так как среднее геометрическое не определено дл€ отрицательных чисел
        if (num < 0.0) {
            printf("Geometric mean is undefined for negative numbers.\n");
            va_end(args);
            return 0.0;
        }
        product *= num;
    }

    va_end(args);

    // ¬ычисление среднего геометрического
    return pow(product, 1.0 / count);
}

// 2. –екурсивна€ функци€ дл€ возведени€ вещественного числа в целую степень
double powerRecursive(double base, int exponent) {
    if (exponent == 0) {
        return 1.0;
    }
    else if (exponent % 2 == 0) {
        // ƒл€ четной степени используем формулу быстрого возведени€ в степень
        double result = powerRecursive(base, exponent / 2);
        return result * result;
    }
    else {
        // ƒл€ нечетной степени используем рекурсию
        return base * powerRecursive(base, exponent - 1);
    }
}

int main() {
    // ѕример использовани€ функции дл€ вычислени€ среднего геометрического
    double geometricMean = calculateGeometricMean(3, 2.0, 3.0, 4.0);
    printf("Geometric mean: %lf\n", geometricMean);

    // ѕример использовани€ рекурсивной функции дл€ возведени€ вещественного числа в степень
    double base = 2.0;
    int exponent = 3;
    double result = powerRecursive(base, exponent);
    printf("%lf raised to the power of %d is %lf\n", base, exponent, result);

    return 0;
}