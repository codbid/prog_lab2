#include <stdio.h>
#include <stdlib.h>
#include "IntVector.h"

IntVector  *int_vector_new(size_t initial_capacity)
{
    IntVector *vector = malloc(sizeof(IntVector));
    if ( !vector )
        return NULL;
    vector->data = calloc(vector->capacity = initial_capacity, sizeof(int));
    if ( !vector->data )
    {
        free(vector);
        return NULL;
    }
    vector->size = 0;
    return vector;
}

IntVector *int_vector_copy(const IntVector *v)
{
    IntVector *vector_new = int_vector_new(v->capacity);
    return vector_new;
}

void int_vector_free(IntVector *v)
{
    free(v);
}

int int_vector_get_item(const IntVector *v, size_t index)
{
    return *(v->data+index);
}

void int_vector_set_item(IntVector *v, size_t index, int item)
{
    if ( int_vector_get_item(v, index) == 0 )
        v->size++;
    else
        v->size--;
    *(v->data+index) = item;
}

size_t int_vector_get_size(const IntVector *v)
{
    return v->size;
}

size_t int_vector_get_capacity(const IntVector *v)
{
    return v->capacity;
}

int int_vector_push_back(IntVector *v, int item)
{
    if (int_vector_get_size(v) < int_vector_get_capacity(v))
        int_vector_set_item(v, int_vector_get_size(v), item);
    else {
        v->data = realloc(v->data, (v->capacity *= 2) * sizeof(int));
        for ( size_t i = int_vector_get_size(v); i < int_vector_get_capacity(v) + 1; i++)
            *(v->data + (size_t)i) = 0;
        int_vector_set_item(v, int_vector_get_size(v), item);
    }
    if (int_vector_get_item(v, int_vector_get_size(v) - 1) == item )
        return 0;
    return -1;
}

void int_vector_pop_back(IntVector *v)
{
    if ( v->size > 0 )
    {
        int_vector_set_item(v, int_vector_get_size(v) - 1, 0);
    }
}

int int_vector_shrink_to_fit(IntVector *v)
{
    v->data = realloc(v->data, (v->capacity = v->size) * sizeof(int));
    if ( v->data )
        return 0;
    return 1;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
        IntVector *vector_backup = int_vector_copy(v);
        if ( new_size >= int_vector_get_size(v) )
        {
            size_t old_size = int_vector_get_size(v);
            for (int i = 0; i < new_size - old_size; i++)
                int_vector_push_back(v, 0);
        } else if ( new_size < int_vector_get_size(v) )
            int_vector_shrink_to_fit(v);
        if ( v->data ) {
            int_vector_free(vector_backup);
            return 0;
        }
        v->data = vector_backup->data;
        int_vector_free(vector_backup);
    return -1;
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
    IntVector *vector_backup = int_vector_copy(v);
    if (int_vector_get_capacity(v) < new_capacity )
    {
        v->data = realloc(v->data, new_capacity * sizeof(int));
        if ( v->data ) {
            int_vector_free(vector_backup);
            v->capacity = new_capacity;
            return 0;
        }
        v->data = vector_backup->data;
    }
    int_vector_free(vector_backup);
    return -1;
}

//
// Created by Daniil on 24.03.2023.
//
