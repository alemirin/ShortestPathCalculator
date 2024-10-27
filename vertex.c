#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "vertex.h"



/**
 * Creates a new vertex struct
 *
 * @param city the name of the vertex city
 * @return a pointer to the new vertex struct
 */
vertex *new_vertex(const char *city, int index)
{
    vertex *newVertex = (vertex *)malloc(sizeof(vertex));
    newVertex->city = strcpy((char *)malloc(strlen(city) + 1), city); // to keep the titles unique
    newVertex->index = index;
    newVertex->prev = NULL;
    return newVertex;
}

/**
 * Frees the memory allocated for a vertex struct
 *
 * @param movie the vertex struct to free
 */
void free_vertex(vertex *vertex)
{
    free((char *)vertex->city);
    free(vertex);
}




