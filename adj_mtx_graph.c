#include <stdio.h>
#include <stdlib.h>
#include "adj_mtx_graph.h"
#include "vertex.h"


graph* create_graph(int numnodes) {
    graph *g = malloc(sizeof(*g));
    if (g == NULL) {
        return NULL;
    }

    g->numnodes = numnodes;
    
    // matrix allocation, initialize to zeroes

    g->edges = calloc(sizeof(int*), g->numnodes);
    if (g->edges == NULL) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < g->numnodes; i++) {
        g->edges[i] = calloc(sizeof(int), g->numnodes);
        if (g->edges[i] == NULL) {
            free_graph(g);
            return NULL;
        }
    }
    return g;


}

void free_graph(graph* g) {
    if (g == NULL) {
        return;
    }
    if (g->edges == NULL) {
        return;
    }

    for (int i = 0; i < g->numnodes; i++) {
        if (g->edges[i] == NULL) {
            free(g->edges[i]);
        }
    }
    free(g->edges);
}

void print_graph(graph *g) {
    if (g == NULL) {
        return;
    }
    printf("Graph: {\n");

    for (int i = 0; i < g->numnodes; i++) {
        for (int j = 0; j < g->numnodes; j++) {
            if (g->edges[i][j]) {
                printf("%d - %d | weight: %d\n", i, j, g->edges[i][j]);
            }
        }
    }
    printf("}\n");
}

bool add_edge(graph *g, unsigned int from, unsigned int to, unsigned int weight) {
    if (g == NULL || from > g->numnodes || to > g->numnodes) {
        return false;
    }
    if (has_edge(g, from, to)) {
        return false;
    }
    
    g->edges[from][to] = weight;
    g->edges[to][from] = weight;
    return true;
}


bool has_edge(graph *g, unsigned int from, unsigned int to) {
    if (g == NULL || from > g->numnodes || to > g->numnodes) {
        return false;
    } 
    if (g->edges[from][to] != 0) {
        return true;
    } 
    return false;
    
}
