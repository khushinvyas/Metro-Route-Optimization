#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 11

int graph[V][V] = {
    {0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Shaheed Sthal to Hindon River (3 km)
    {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0}, // Hindon River to Arthala (2 km)
    {0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0}, // Arthala to Mohan Nagar (7 km)
    {0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0}, // Mohan Nagar to Shyam Park (9 km)
    {0, 0, 0, 0, 0, 10, 0, 0, 9, 0, 0},// Shyam Park to Major Mohit Sharma(10 km) and Dilshad Garden (9 km)
    {0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0}, // Major Mohit Sharma to Raj Bagh (2 km) and Shaheed nagar (3 km)
    {0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0},// Raj Bagh to shaheed nagar (3 km) 
    {0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0},// sheed nagar to dishad (4 km)
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0},// dilshad to jhil mil (5 km)
    {0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0},// jhil mil to arthala (5 km )
    {8, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0},// mansarovar to sheed sthal (8km) and arthala (6 km)
};

char *metroNames[V] = {
    "Shaheed Sthal(First Station)",
    "Hindon River",
    "Arthala",
    "Mohan Nagar",
    "Shyam Park",
    "Major Mohit Sharma",
    "Raj Bagh",
    "Shaheed Nagar",
    "Dilshad Garden",
    "Jhil Mil",
    "Mansarovar Park"
};

// Function to find the station with the minimum distance value
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the shortest path from the source station to the destination station
void printShortestPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    
    printShortestPath(parent, parent[j]);
    printf(" -> %s", metroNames[j]);
}

// Function to find the shortest path between two stations using Dijkstra's algorithm
void dijkstra(int src, int dest) {
    int dist[V];
    bool sptSet[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;
    parent[src] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        printf("No path found between %s and %s\n", metroNames[src], metroNames[dest]);
    } else {
        printf("Shortest path from %s to %s: %s", metroNames[src], metroNames[dest], metroNames[src]);
        printShortestPath(parent, dest);
        printf("\nTotal Distance: %d km\n", dist[dest]);
        
        // Calculate and print the total time taken
        int time = dist[dest] * 2; // Metro travels 1 km in 2 minutes
        printf("Total Time Taken: %d minutes\n", time);
    }
}

// Function to print all stations and their distances
void printAllStationsAndDistances() {
    printf("Metro Stations and Distances:\n");
    for (int i = 0; i < V; i++) {
        printf("%d. %s: ", i, metroNames[i]);
        for (int j = 0; j < V; j++) {
            if (graph[i][j] > 0) {
                printf("%s(%d km) ", metroNames[j], graph[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int src, dest;

    printAllStationsAndDistances();

    printf("\nEnter the source station (0 to 10): ");
    scanf("%d", &src);
    printf("Enter the destination station (0 to 10): ");
    scanf("%d", &dest);

    dijkstra(src, dest);

    return 0;
}
