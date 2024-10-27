#ifndef ADJ_MTX_GRAPH_H
#define ADJ_MTX_GRAPH_H


#include <stdbool.h>
#include "vertex.h"

typedef struct mygraph {
    int numnodes;
    int** edges;
} graph;

typedef struct myvertex vertex;


graph* create_graph(int numnodes);
void free_graph(graph* g);
void print_graph(graph* g);
bool add_edge(graph *g, unsigned int from, unsigned int to, unsigned int weight);
bool has_edge(graph *g, unsigned int from, unsigned int to);

#endif