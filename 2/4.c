#include <stdio.h>
#include <stdarg.h>  // Для работы с переменным числом аргументов
#include <math.h>    // Для использования функции fabs

// Функция для определения выпуклости многоугольника
int isConvexPolygon(int numVertices, ...) {
    va_list args;
    va_start(args, numVertices);

    // Проверка для треугольника, так как любой треугольник является выпуклым
    if (numVertices < 3) {
        va_end(args);
        return 1;  // Многоугольник с меньшим числом вершин считается выпуклым
    }

    double prevCrossProduct = 0.0;

    // Первая вершина
    double x1 = va_arg(args, double);
    double y1 = va_arg(args, double);

    // Вторая вершина
    double x2 = va_arg(args, double);
    double y2 = va_arg(args, double);

    // Третья вершина
    double x3 = va_arg(args, double);
    double y3 = va_arg(args, double);

    // Векторное произведение для первых трех вершин
    double crossProduct = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
    prevCrossProduct = crossProduct;

    // Проверка для остальных вершин
    for (int i = 3; i < numVertices * 2; i += 2) {
        // Следующая вершина
        double x = va_arg(args, double);
        double y = va_arg(args, double);

        // Векторное произведение
        crossProduct = (x2 - x1) * (y - y2) - (y2 - y1) * (x - x2);

        // Проверка изменения знака векторного произведения
        if (crossProduct * prevCrossProduct < 0) {
            va_end(args);
            return 0;  // Знак векторного произведения изменился, многоугольник невыпуклый
        }

        // Переход к следующей вершине
        x1 = x2;
        y1 = y2;
        x2 = x;
        y2 = y;
        prevCrossProduct = crossProduct;
    }

    va_end(args);
    return 1;  // Многоугольник остался выпуклым
}

// Функция для вычисления значения многочлена
double polynomialValue(double x, int degree, ...) {
    va_list args;
    va_start(args, degree);

    double result = 0.0;

    for (int i = degree; i >= 0; i--) {
        double coefficient = va_arg(args, double);
        result += coefficient * pow(x, i);
    }

    va_end(args);
    return result;
}

int main() {
    // Пример использования функции для проверки выпуклости многоугольника
    int convex = isConvexPolygon(4, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0);
    if (convex) {
        printf("Многоугольник выпуклый.\n");
    }
    else {
        printf("Многоугольник невыпуклый.\n");
    }

    // Пример использования функции для вычисления значения многочлена
    double value = polynomialValue(2.0, 3, 1.0, -2.0, 0.0, 3.0);
    printf("Значение многочлена в точке x=2.0: %f\n", value);

    return 0;
}