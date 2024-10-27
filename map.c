#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "adj_mtx_graph.h"
#include "djikstras.h"
#include "file_handler.h"
#include "vector.h"
#include "vertex.h"

#define delim " "
#define MAX_BUFF 1000


void print_help() {
    printf("\tlist - list all cities\n");
    printf("\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\thelp - print this help message\n");
    printf("\texit - exit the program\n");
    printf("\n");
}


int main(int argc, const char* argv[]) {
    if (argc < 2)
    {
        printf("Missing input files\n");
        return 1; // ends with an error signal
    }

    const char* input_file_cities = argv[1];
    if(input_file_cities == NULL) {
        printf("No input file provided\n");
        return 1; // ends with an error signal
    }

    const char* input_cities_distances = argv[2];
    if(input_cities_distances == NULL) {
        printf("No city distance file provided\n");
        return 1; // ends with an error signal
    }

    //Create vector with all city names
    CityVector *vector = load_cities(input_file_cities);
    if(vector == NULL) {
        return 1; // error printed in load_cities, but ending program as vector needs to exist
    }


    //Create weighted adjacency matrix graph with cities.
    graph* city_graph = load_cities_distances(input_cities_distances, vector);
    if(city_graph == NULL) {
        return 1; // error printed in load_cities_distances, but ending program as graph needs to exist
    }

    //Create string for city name list
    char* str = vector_to_str(vector);

    char input[MAX_BUFF];
    printf("****Welcome to the shortest path finder!****\n");
    printf("Commands:\n");
    printf("\tlist - list all cities\n");
    printf("\t<city1> <city2> - find shortest path between two cities\n");
    printf("\thelp - print this help message\n");
    printf("\texit - exit the program\n");
    printf("*******************************************************\n");
    printf("Where do you want to go today? ");

    while(true) 
    {
        //read user input
        fgets(input, MAX_BUFF, stdin);

        //change newline character to \0
        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '\0') {
            continue;
        }
        else if (strcmp("exit", input) == 0) {
            return 1;
        }
        else if (strcmp("list",input) == 0) {
            printf("%s",str);
            printf("Where do you want to go today? ");
        }
        else if (strcmp("help", input) == 0) {
            printf("Commands:\n");
            print_help();
            printf("Where do you want to go today? ");
        }
        else {
            char* arg1 = strtok(input, delim);
            char* arg2 = strtok(NULL, "\n");
            int ind1 = 0;
            int ind2 = 0;
            int found = 0;

            //Check to see that arguments inputted are cities within our list
            for (int i = 0; i < vector->size; i++) {
                if (strcmp(vector->vertices[i]->city, arg1) == 0) {
                    found++;
                    ind1 = i;
                    if (found == 2) {
                        break;
                    }
                }
                if (strcmp(vector->vertices[i]->city, arg2) == 0) {
                    found++;
                    ind2 = i;
                    if (found == 2) {
                        break;
                    }
                }
            }

            //If arguments are not valid or not cities loaded in our current run,
            //Notify the user
            if (found < 2) {
                printf("Invalid Command\n");
                printf("Commands:\n");
                print_help();
                printf("Where do you want to go today? ");
            } 
            //If both arguments are cities and they are equal, we are already at our destination
            else if (strcmp(arg1,arg2) == 0) {
                printf("Already at destination.\n");
                printf("Where do you want to go today? ");
            }
            else {
                //execute djikstras with adjacency matrix
                dijkstra(city_graph, ind1, ind2, vector->size, vector);

                printf("\nWhere do you want to go today? ");
            }
        }
    }
    free_vector(vector);
    free_graph(city_graph);
    free(str);
}
