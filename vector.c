/** 
 * Implementation of CityVector (vector.h) 
 * 
 * 
 * 
 * @author Alejandro Miranda 
*/

#include "vector.h"

/**
 * Creates a new CityVector.
 * 
 * @return a pointer to the new CityVector
*/
CityVector *new_vector() {
    CityVector *vector = (CityVector *) malloc(sizeof(CityVector));
    vector->vertices = (vertex **) malloc(sizeof(vertex *) * INITIAL_CAPACITY);
    vector->capacity = INITIAL_CAPACITY;
    vector->size = 0;
    return vector;
}

/**
 * Frees the memory associated with a CityVector.
 * This does not free the vertex structs, just the vector itself.
 * 
 * @param vector the CityVector to free
*/
void free_vector(CityVector *vector) {
    free(vector->vertices);
    free(vector);
}

/**
 * Frees the memory associated with CityVector, including the vertices.
 * 
 * @param vector the CityVector to free
*/
void clear_and_free_vector(CityVector *vector) {
    for (int i = 0; i < vector->size; i++) {
        free_vector(vector);
    }
    free(vector->vertices);
    free(vector);
}

/**
 * Doubles the size of the vector for reallocation.
 * 
 * Using __ to indicate this is a private function, and should not be 
 * used outside of this file.
 * 
 * @param vector the vector to double
*/
void __double_vector(CityVector *vector) {
    vector->capacity *= RESIZE_FACTOR;  
    vector->vertices = (vertex **) realloc(vector->vertices, sizeof(vertex *) * vector->capacity);
    
}

/**
 * Inserts a vertex into a CityVector at a given index.
 * 
 * May add at the end by passing in the size of the vector.
 * 
 * Does nothing if the index is out of bounds.
 * 
 * @param vector the CityVector to insert into
 * @param vertex the vertex to insert
 * 
*/
void vector_insert(CityVector *vector, vertex *vertex) {
    if (vector->size == vector->capacity) {
        __double_vector(vector);
    }
    vector->vertices[vertex->index] = vertex;
    vector->size++;
}

/**
 * Checks if the vector is empty.
 * 
 * @param vector the vector to check
 * @return true if the vector is empty, false otherwise
*/
bool vector_is_empty(CityVector *vector) {
    return vector->size == 0;
}

/**
 * Converts the vector to a string representation.
 * 
 * @param vector the vector to convert
 * @return the string representation
*/
char *vector_to_str(CityVector *vector) {
    char *str = (char *)calloc(vector->size, sizeof(char) * (MAX_CITY_STR_LEN + 3));
    if (vector_is_empty(vector)){
        strcpy(str, "[]");
        return str; // early exit
    }
    for (int i = 0; i < vector->size; i++) {
        char *city_str = vector->vertices[i]->city;
        /*
        if (i == 0) {
            str = city_str;
        } else {
            strcat(str, city_str);
        }
        */
        strcat(str, city_str);
        if (i != vector->size - 1) {
            strcat(str, "\n");
        }
    }
    strcat(str, "\n");
    return str;
}

int find_index(char* city, CityVector* vector) {
    for (int i = 0; i < vector->size; i++) {
        if (strcmp(city, vector->vertices[i]->city) == 0) {
            return i;
        }
    }
    return -1;
}