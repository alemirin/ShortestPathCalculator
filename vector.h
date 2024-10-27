#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "vertex.h"


#define INITIAL_CAPACITY 10000
#define RESIZE_FACTOR 2

typedef struct Vector {
    vertex** vertices;  
    int size;
    int capacity;
} CityVector;

CityVector * new_vector();
void free_vector(CityVector * vector);
void clear_and_free_vector(CityVector * vector);
void vector_insert(CityVector *vector, vertex *vertex);
bool vector_is_empty(CityVector * vector);
char* vector_to_str(CityVector * vector);
int find_index(char* city, CityVector* vector);


#endif