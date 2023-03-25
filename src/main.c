#include <stdio.h>
#include "IntVector.h"
//#include <windows.h>
#include <locale.h>
int main()
{
    setlocale(LC_ALL, "Rus");
    //SetConsoleOutputCP(CP_UTF8);
    IntVector *v = int_vector_new(5);
    int_vector_push_back(v, 3); int_vector_push_back(v, 2);
    printf("Создаём вектор v ёмкости %zu, присваиваем его нулевому элементу %d и первому элементу %d, размер сейчас равен %zu\n",
           int_vector_get_capacity(v), int_vector_get_item(v, 0), int_vector_get_item(v, 1), int_vector_get_size(v));
    int_vector_pop_back(v);
    printf("Удалим последний элемент (в нашем случае, с индексом 1), тогда нулевой элемент будет так же равен %d, первый станет %d, при этом размер теперь будет %zu\n",
           int_vector_get_item(v, 0), int_vector_get_item(v, 1), int_vector_get_size(v));
    printf("Сейчас размер вектора равен %zu, а ёмкость %zu\n", int_vector_get_size(v), int_vector_get_capacity(v));
    int_vector_shrink_to_fit(v);
    printf("Сократим ёмкость вектора до его размера, теперь размер %zu, ёмкость %zu\n", int_vector_get_size(v),
           int_vector_get_capacity(v));
    int_vector_resize(v, 8);
    printf("Установим вектору размер %zu, его ёмкость стала равна %zu (step 1: 2*2, step 2: 4*2)\n", int_vector_get_size(v), int_vector_get_capacity(v));
    int_vector_reserve(v, 6);
    printf("Установим вектору ёмкость 6, но она всё равно останется равна %zu, т.к. мы пытаемся установить ёмкость меньше текущей\n", int_vector_get_capacity(v));
    int_vector_reserve(v, 11);
    printf("Установим вектору ёмкость %zu\n", int_vector_get_capacity(v));
    printf("После всех манипуляций выведем элементы, которые мы установили в начале (нулевой: %d, первый: %d)\n",
           int_vector_get_item(v, 0), int_vector_get_item(v, 1));
}