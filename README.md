# Finding The Shortest Distance

Compile using `clang -Wall -o map.out adj_mtx_graph.c vertex.c vector.c djikstras.c map.c` in the terminal.

Afterwards, provide a list of cities/vertices and a list of distances between cities, both as .txt or .dat files, as a command line argument.

- `Usage: ./map.out <vertices> <distances>`
- After the information is loaded, the application will ask: `Where do you want to go today?`
  - They will have the following options for input:
    - list - list all cities
    - \<city1> \<city2> - find the shortest path between two cities
    - help - print this help message
    - exit - exit the program
  - If they type anything that is not in the above option, or a city not in the city list, it will prompt an invalid option and print the help message (see below - for sample runs).
- When two cities are entered:
  - It will print the `shortest path` from city one to city two, and the total distance.
  - If there is no path, it will print `Path Not Found...`
