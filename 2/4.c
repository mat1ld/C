#include <stdio.h>
#include <stdarg.h>  // ��� ������ � ���������� ������ ����������
#include <math.h>    // ��� ������������� ������� fabs

// ������� ��� ����������� ���������� ��������������
int isConvexPolygon(int numVertices, ...) {
    va_list args;
    va_start(args, numVertices);

    // �������� ��� ������������, ��� ��� ����� ����������� �������� ��������
    if (numVertices < 3) {
        va_end(args);
        return 1;  // ������������� � ������� ������ ������ ��������� ��������
    }

    double prevCrossProduct = 0.0;

    // ������ �������
    double x1 = va_arg(args, double);
    double y1 = va_arg(args, double);

    // ������ �������
    double x2 = va_arg(args, double);
    double y2 = va_arg(args, double);

    // ������ �������
    double x3 = va_arg(args, double);
    double y3 = va_arg(args, double);

    // ��������� ������������ ��� ������ ���� ������
    double crossProduct = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
    prevCrossProduct = crossProduct;

    // �������� ��� ��������� ������
    for (int i = 3; i < numVertices * 2; i += 2) {
        // ��������� �������
        double x = va_arg(args, double);
        double y = va_arg(args, double);

        // ��������� ������������
        crossProduct = (x2 - x1) * (y - y2) - (y2 - y1) * (x - x2);

        // �������� ��������� ����� ���������� ������������
        if (crossProduct * prevCrossProduct < 0) {
            va_end(args);
            return 0;  // ���� ���������� ������������ ���������, ������������� ����������
        }

        // ������� � ��������� �������
        x1 = x2;
        y1 = y2;
        x2 = x;
        y2 = y;
        prevCrossProduct = crossProduct;
    }

    va_end(args);
    return 1;  // ������������� ������� ��������
}

// ������� ��� ���������� �������� ����������
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
    // ������ ������������� ������� ��� �������� ���������� ��������������
    int convex = isConvexPolygon(4, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0);
    if (convex) {
        printf("������������� ��������.\n");
    }
    else {
        printf("������������� ����������.\n");
    }

    // ������ ������������� ������� ��� ���������� �������� ����������
    double value = polynomialValue(2.0, 3, 1.0, -2.0, 0.0, 3.0);
    printf("�������� ���������� � ����� x=2.0: %f\n", value);

    return 0;
}