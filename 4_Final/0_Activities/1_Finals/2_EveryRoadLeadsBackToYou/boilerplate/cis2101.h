#ifndef CIS2101_H
#define CIS2101_H

#define MAX_CITIES 10

// Define a structure for an adjacency list node
typedef struct Node {
    int destination;
    int weight;
    struct Node* next;
} Node;

// Define a structure for the graph
typedef struct Graph {
    int cityCount;
    Node* adjList[MAX_CITIES]; // Array of adjacency lists
} Graph;

// Define a structure for the priority queue (min-heap)
typedef struct PriorityQueue {
    int vertices[MAX_CITIES];
    int dist[MAX_CITIES];
    int size;
} PriorityQueue;

// Function to create a new adjacency list node
Node* createNode(int dest, int weight);

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight);

// Function to initialize the priority queue
void initPriorityQueue(PriorityQueue* pq, int cityCount);

// Function to swap two elements in the priority queue
void swap(PriorityQueue* pq, int i, int j);

// Function to heapify the priority queue
void heapify(PriorityQueue* pq, int i);

// Function to extract the minimum distance vertex from the priority queue
int extractMin(PriorityQueue* pq);

// Function to decrease the key (update the distance) of a vertex in the priority queue
void decreaseKey(PriorityQueue* pq, int vertex, int newDist);

// Function to reconstruct the shortest path
void reconstructPath(int prev[], int start, int end);

#endif