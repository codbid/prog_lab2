#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    memcpy(vector_new->data, v->data, v->capacity * sizeof(int));
    vector_new->size = v->size;
    return vector_new;
}

void int_vector_free(IntVector *v)
{
    free(v->data);
    free(v);
}

int int_vector_get_item(const IntVector *v, size_t index)
{
    return *(v->data+index);
}

void int_vector_set_item(IntVector *v, size_t index, int item)
{
    *(v->data+index) = item;
    if ( index == v->size )
        v->size++;
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
    if (v->size < v->capacity)
        int_vector_set_item(v, v->size, item);
    else {
        v->data = realloc(v->data, (v->capacity *= 2) * sizeof(int));
        for ( size_t i = v->size; i < v->capacity + 1; i++)
            *(v->data + (size_t)i) = 0;
        int_vector_set_item(v, v->size, item);
    }
    if (int_vector_get_item(v, v->size - 1) == item )
        return 0;
    return -1;
}

void int_vector_pop_back(IntVector *v)
{
    if ( v->size > 0 )
    {
        int_vector_set_item(v, v->size - 1, 0);
        v->size--;
    }
}

int int_vector_shrink_to_fit(IntVector *v)
{   if ( v->size != v->capacity )
    {
        v->data = realloc(v->data, (v->capacity = v->size) * sizeof(int));
        if ( v->data )
            return 0;
    }
    return -1;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
    int *data_backup = calloc(v->capacity, sizeof(int));
    memcpy(data_backup, v->data, v->capacity * sizeof(int));
    if ( new_size >= v->size )
    {
        size_t old_size = v->size;
        for (int i = 0; i < new_size - old_size; i++)
            int_vector_push_back(v, 0);
    } else if ( new_size < v->size )
        while ( v->size > new_size )
            int_vector_pop_back(v);
    if ( v->data ) {
        free(data_backup);
        return 0;
    }
    memcpy(v->data, data_backup, v->capacity * sizeof(int));
    free(data_backup);
    return -1;
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
    int *data_backup = calloc(v->capacity, sizeof(int));
    memcpy(data_backup, v->data, v->capacity * sizeof(int));
    if (v->capacity < new_capacity )
    {
        v->data = realloc(v->data, new_capacity * sizeof(int));
        if ( v->data ) {
            free(data_backup);
            v->capacity = new_capacity;
            for ( size_t i = v->size; i < v->capacity + 1; i++)
                *(v->data + (size_t)i) = 0;
            return 0;
        }
        memcpy(v->data, data_backup, v->capacity * sizeof(int));
    }
    free(data_backup);
    return -1;
}

//
// Created by Daniil on 24.03.2023.
//
