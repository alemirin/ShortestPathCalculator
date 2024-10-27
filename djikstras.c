#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "djikstras.h"
#include "adj_mtx_graph.h"
#include "vector.h"
#include "vertex.h"



int minDistance(int costs[], bool visited[], int size)
{
    // Initialize minimum value
    int min = INT_MAX;
    int min_index;
 
    for (int v = 0; v < size; v++)
        if (visited[v] == false && costs[v] <= min)
            min = costs[v], min_index = v;
 
    return min_index;
}


void printTraversal(int path[], int source, int destination, CityVector* vector, int costs[])
{   
    //if there exists a path from source to destination
    if (costs[destination] != INT_MAX) {

        int d = destination; 

        //initialize array to store path starting from destination to source
        int back_path[vector->size];

        int count = 0;

        //travel through the path array to find the order of location indeces
        //from destination to source
        for (int z = 0; z < vector->size; z++) {
            //add current city index to back_path
            back_path[z] = d; 

            //reset d to next city index to visit
            d = path[d]; 

            count++;

            //check if source city has been reached
            if (d == source || d == -1) {
                back_path[z + 1] = source;
                break;
            }
        }

        /*
        printf("Index  |  Parent Array  |  Back_path\n");
        for (int j = 0; j < vector->size; j++) {
            printf("%d  |  %d  |  %d\n", j, path[j], back_path[j]);
        }
        */

        //Loop backwards through backwards path array and print the location in 
        //order to output correct order for traversal
        for (int c = count; c >= 0; c--) {
            printf("%s\n", vector->vertices[back_path[c]]->city);
        }

        printf("Total Distance: %d", costs[destination]);
        
    } else {
        printf("Path Not Found...\n");
    }
}

void dijkstra(graph *g, int source, int destination, int size, CityVector* vector) 
{
    //declare array to hold the shortest path from source to 
    //destination and all current paths
    int *costs = malloc(size * sizeof(costs));

    //declare array to store visited nodes
    bool visited[size];

    //declare array to store origin vertex for each vertex
    int *path = malloc(size * sizeof(path));

    //initialize all distances as max int value and the
    //visited array items as false
    for (int i = 0; i < size; i++) {
        costs[i] = INT_MAX;
        visited[i] = false;
        path[i] = -1;
    }

    //set distance of source vertex to 0
    costs[source] = 0;
    

    // Find shortest path for all vertices
    for (int a = 0; a < size; a++) {
        //Find current minimum cost's index within the list of unvisited vertices
        int curr_min = minDistance(costs, visited, size);
 
        //Mark the picked vertex as processed
        visited[curr_min] = true;
 
        // Update cost of the adjacent vertices of the
        // current vertex.
        for (int v = 0; v < size; v++) {
            // Only if the vertex has not been visited, there exists an edge between the picked vertex
            // and the current vertex, and the cost of the path to the picked vertex is lower than the current cost
            // value, update costs array and update previous vertex pointer for current vertex
            if (!visited[v] && g->edges[curr_min][v]
                && costs[curr_min] != INT_MAX
                && costs[curr_min] + g->edges[curr_min][v] < costs[v]) {

                //update cost at vertex
                costs[v] = costs[curr_min] + g->edges[curr_min][v];

                //set previous city vertex pointer
                //for our new edge to the current vertex we are comparing to
                path[v] = curr_min;
                
            }
        } 
    }
    printTraversal(path, source, destination, vector, costs);
    free(path);
    free(costs);
    return;
    
}