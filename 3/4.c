#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Определение типа структуры String
typedef struct {
    char* data;  // Указатель на динамический массив символов
    int length;  // Количество символов (длина строки)
} String;

// Функция создания экземпляра типа String на основе значения типа char *
String createString(const char* initial) {
    String newString;

    // Выделение памяти для копирования переданной строки
    newString.data = strdup(initial);

    if (newString.data == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Вычисление длины строки
    newString.length = strlen(initial);

    return newString;
}

// Функция удаления внутреннего содержимого экземпляра типа String
void deleteStringContent(String* str) {
    free(str->data);  // Освобождение выделенной динамической памяти
    str->data = NULL;  // Установка указателя в NULL
    str->length = 0;   // Установка длины в 0
}

// Функция отношения порядка между двумя экземплярами типа String
int compareStrings(const String* str1, const String* str2) {
    // Сначала сравниваем по длине
    if (str1->length < str2->length) return -1;
    if (str1->length > str2->length) return 1;

    // Если длины равны, используем лексографический компаратор
    return strcmp(str1->data, str2->data);
}

// Функция отношения эквивалентности между двумя экземплярами типа String
int areStringsEqual(const String* str1, const String* str2) {
    return (compareStrings(str1, str2) == 0);
}

// Функция копирования содержимого экземпляра типа String в существующий экземпляр
void copyString(String* destination, const String* source) {
    // Освобождение текущего содержимого
    deleteStringContent(destination);

    // Выделение новой памяти и копирование данных
    destination->data = strdup(source->data);

    if (destination->data == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Установка новой длины
    destination->length = source->length;
}

// Функция копирования содержимого экземпляра типа String в новый экземпляр
String copyStringToNew(const String* source) {
    return createString(source->data);
}

// Функция конкатенации к содержимому первого экземпляра типа String содержимого второго
String concatenateStrings(const String* str1, const String* str2) {
    String result;

    // Выделение памяти для конкатенированной строки
    result.data = (char*)malloc(str1->length + str2->length + 1);

    if (result.data == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Копирование данных и установка новой длины
    strcpy(result.data, str1->data);
    strcat(result.data, str2->data);
    result.length = str1->length + str2->length;

    return result;
}

int main() {
    // Пример использования
    String s1 = createString("Hello");
    String s2 = createString("World");

    printf("Comparison result: %d\n", compareStrings(&s1, &s2));
    printf("Equality result: %d\n", areStringsEqual(&s1, &s2));

    String s3;
    copyString(&s3, &s1);

    String s4 = copyStringToNew(&s2);

    String s5 = concatenateStrings(&s1, &s2);

    // Освобождение ресурсов
    deleteStringContent(&s1);
    deleteStringContent(&s2);
    deleteStringContent(&s3);
    deleteStringContent(&s4);
    deleteStringContent(&s5);

    return 0;
}
