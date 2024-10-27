/**
 * Various functions for handling files.
 * 
 * @author Alejandro Miranda
*/

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include "vertex.h"
#include "vector.h"
#include "adj_mtx_graph.h"

/**
 * Loads the input file into a vector of vertices representing cities.
 * 
 * It assumes that the input file has a single city on each line.
 * 
 * 
 * For IDs, it will just use the line number.
 * 
 * @param filename The name of the file to load.
 * @return A vector of vertices. NULL if there is an error
*/
CityVector * load_cities(const char* filename) {
    CityVector * vector = new_vector();
    FILE * file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file: %s", filename);
        return NULL; 
    }
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int ind = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        if (line[read - 1] == '\n') {
            // remove the newline character
            line[read - 1] = '\0';
        }
        vertex * vertex = new_vertex(line, ind);
        vector_insert(vector, vertex);
        ind++;
    }
    fclose(file);
    if (line) {
        free(line);
    }
    return vector;
}

/**
 * Loads the input file into a vector of vertices representing cities.
 * 
 * It assumes that the input file has a single city on each line.
 * 
 * 
 * For IDs, it will just use the line number.
 * 
 * @param filename The name of the file to load.
 * @return A vector of vertices. NULL if there is an error
*/
graph * load_cities_distances(const char* filename, CityVector* vector) {
    graph * city_graph = create_graph(vector->size);
    FILE * file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file: %s", filename);
        return NULL; 
    }
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        if (line[read - 1] == '\n') {
            // remove the newline character
            line[read - 1] = '\0';
        }

        // split line into two cities and distance
        char* city1 = strtok(line, " ");
        char* city2 = strtok(NULL, " ");
        unsigned int distance = atoi(strtok(NULL, "\n"));

        //printf("%s  | %s  | %d\n", city1, city2, distance);


        // find city names in city vector and get indices of both
        int index1 = find_index(city1, vector);
        int index2 = find_index(city2, vector);

        if (index1 == -1 || index2 == -1) {
            printf("City not found in data.");
            return NULL;
        }

        
        // add edge into adjacency matrix graph representing path
        add_edge(city_graph, index1, index2, distance);
    }
    fclose(file);
    if (line) {
        free(line);
    }
    return city_graph;
}


#endif