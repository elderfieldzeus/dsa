#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "cis2101.h"

// find the shortest path
void shortestPath(Graph* graph, int start, int end, int dist[], int prev[]) {
    PriorityQueue pq;
    // To do code logic here
    
}

int main() {
    Graph graph;
    printf("Enter the number of cities: ");
    scanf("%d", &graph.cityCount);

    // Initialize adjacency list
    for (int i = 0; i < graph.cityCount; i++) {
        graph.adjList[i] = NULL;
    }

    int edgeCount;
    printf("Enter the number of edges: ");
    scanf("%d", &edgeCount);

    printf("Enter the edges (source destination weight) for %d edges:\n", edgeCount);
    for (int i = 0; i < edgeCount; i++) {
        int src, dest, weight;
        printf("Enter edge %d (source destination weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(&graph, src, dest, weight);
    }

    int start, end;
    printf("Enter the source city (0 to %d): ", graph.cityCount - 1);
    scanf("%d", &start);

    printf("Enter the destination city (0 to %d): ", graph.cityCount - 1);
    scanf("%d", &end);

    int dist[MAX_CITIES], prev[MAX_CITIES];
    for (int i = 0; i < graph.cityCount; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    shortestPath(&graph, start, end, dist, prev);

    if (dist[end] == INT_MAX) {
        printf("There is no path from city %d to city %d\n", start, end);
    } else {
        printf("The shortest distance from city %d to city %d is %d\n", start, end, dist[end]);
        reconstructPath(prev, start, end);
    }

    return 0;
}