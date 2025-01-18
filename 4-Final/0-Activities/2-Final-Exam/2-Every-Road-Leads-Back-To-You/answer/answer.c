#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "cis2101.h"

// // Define a structure for an adjacency list node
// typedef struct Node {
//     int destination;
//     int weight;
//     struct Node* next;
// } Node;

// // Define a structure for the graph
// typedef struct Graph {
//     int cityCount;
//     Node* adjList[MAX_CITIES]; // Array of adjacency lists
// } Graph;

// // Define a structure for the priority queue (min-heap)
// typedef struct PriorityQueue {
//     int vertices[MAX_CITIES];
//     int dist[MAX_CITIES];
//     int size;
// } PriorityQueue;

// // Function to extract the minimum distance vertex from the priority queue
// int extractMin(PriorityQueue* pq);

// // Function to decrease the key (update the distance) of a vertex in the priority queue
// void decreaseKey(PriorityQueue* pq, int vertex, int newDist);

// // Function to reconstruct the shortest path
// void reconstructPath(int prev[], int start, int end);

void displayQueue(PriorityQueue pq) {
    printf("PQ:\n");
    for(int i = 0; i < pq.size; i++) {
        printf("%d %d\n", pq.vertices[i], pq.dist[i]);
    }
}

// find the shortest path
void shortestPath(Graph* graph, int start, int end, int dist[], int prev[]) {
    PriorityQueue pq;
    // To do code logic here
    int visited[graph->cityCount];
    
    for(int i = 0; i < graph->cityCount; i++) {
        visited[i] = 0;
    }
    
    visited[start] = 1;
    
    initPriorityQueue(&pq, graph->cityCount); // size doesnt seem to change
    pq.size = graph->cityCount;
    decreaseKey(&pq, start, 0);
    dist[start] = 0;
    prev[start] = start;
    decreaseKey(&pq, start, 0);
    int count = 0;
    
    // initialize prio queue
    for(Node *trav = graph->adjList[start]; trav != NULL; trav = trav->next) {
        dist[trav->destination] = trav->weight;
        decreaseKey(&pq, trav->destination, trav->weight);
        prev[trav->destination] = start;
        count++;
    }
    

    
    for(int i = 1; i < graph->cityCount; i++) {
        int minVertex = extractMin(&pq);
        // printf("%d", minVertex);
        
        while(pq.size > 0 && visited[minVertex] == 1) {
            minVertex = extractMin(&pq);
        }
        
        // if minVertex is not yet visited
        if(minVertex != -1) {
            visited[minVertex] = 1;
            for(Node *trav = graph->adjList[minVertex]; trav != NULL; trav = trav->next) {
                int newWeight = dist[minVertex] + trav->weight;
                if(dist[minVertex] != INT_MAX && newWeight < dist[trav->destination]) {
                    // printf("%d %d\n\n", trav->destination, newWeight);
                    dist[trav->destination] = newWeight;
                    decreaseKey(&pq, trav->destination, newWeight);
                    prev[trav->destination] = minVertex;
                    // printf("%d %d\n", trav->destination, minVertex);
                }
            }
        }
    }
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