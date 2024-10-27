#ifndef DJIKSTRAS_H
#define DJIKSTRAS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "vertex.h"
#include "adj_mtx_graph.h"

int minDistance(int costs[], bool visited[], int size);
void printTraversal(int path[], int source, int destination, CityVector* vector, int costs[]);
void dijkstra(graph *g, int source, int destination, int size, CityVector* vector);





#endif