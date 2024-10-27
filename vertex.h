#ifndef VERTEX_H
#define VERTEX_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CITY_STR_LEN 30\

typedef struct myvertex vertex;

typedef struct myvertex {
    char* city;
    int index;
    vertex* prev;
    
} vertex;

vertex *new_vertex(const char *city, int index);
void free_vertex(vertex *vertex);


#endif