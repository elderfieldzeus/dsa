#include <stdio.h>
#include <stdlib.h>
#define MAX 6
#define MAX_SIZE 20
#define infinity 999

typedef struct node {
    int label;
    int weight;
    struct node *next;
} *Vertex;

typedef Vertex AdjList[MAX];

typedef struct {
    int u, v;
    int weight;
} EdgeType;

typedef struct {
    EdgeType edges[MAX_SIZE];
    int lastNdx;
} MinHeapList;

typedef struct {
    MinHeapList eList;
    int cost;
} MST; 

typedef int Set[MAX]; // bit-vector

MST Prims(AdjList M, int start);

void initList(AdjList M);
void insertEdge(AdjList M, EdgeType edge);
void minHeapify(MinHeapList *L, int parent);
void insertMinHeap(MinHeapList *L, EdgeType edge);
EdgeType deleteMin(MinHeapList *L);
void displayMinHeap(MinHeapList PQ);
void displayEdges(MST P);


int main() {
    AdjList M;
    initList(M);

    
    insertEdge(M, (EdgeType){1, 0, 1});
    insertEdge(M, (EdgeType){1, 2, 5});
    insertEdge(M, (EdgeType){1, 5, 6});
    insertEdge(M, (EdgeType){5, 0, 5});
    insertEdge(M, (EdgeType){2, 0, 4});
    insertEdge(M, (EdgeType){4, 5, 3});
    insertEdge(M, (EdgeType){4, 3, 1});
    insertEdge(M, (EdgeType){2, 3, 2});
    insertEdge(M, (EdgeType){4, 0, 6});
    insertEdge(M, (EdgeType){3, 0, 4});


    MST P = Prims(M, 0);
    printf("Minimum weight is %d.\n", P.cost);
    displayEdges(P);

    return 0;
}

MST Prims(AdjList M, int start) {
    MST P = {{.lastNdx = -1}, 0};
    MinHeapList PQ = {.lastNdx = -1};

    Set visited = {};
    visited[start] = 1;

    for(Vertex curr = M[start]; curr != NULL; curr = curr->next) {
        insertMinHeap(&PQ, (EdgeType){start, curr->label, curr->weight});
    }

    int numOfEdges = MAX - 1;

    while(P.eList.lastNdx + 1 < numOfEdges) {
        EdgeType min = deleteMin(&PQ);

        if(visited[min.u] != visited[min.v]) {
            P.cost += min.weight;

            P.eList.edges[++P.eList.lastNdx] = min;

            int notVisited = (visited[min.u] == 0) ? min.u : min.v;
            visited[notVisited] = 1;

            for(Vertex curr = M[notVisited]; curr != NULL; curr = curr->next) {
                if(visited[curr->label] == 0) {
                    insertMinHeap(&PQ, (EdgeType){notVisited, curr->label, curr->weight});
                }
            }
        }
    }

    return P;
}

void initList(AdjList M) {
    for(int i = 0; i < MAX; i++) {
        M[i] = NULL;
    }
}

void insertEdge(AdjList M, EdgeType edge) {
    Vertex temp = (Vertex) malloc(sizeof(struct node));

    if(temp != NULL) {
        temp->label = edge.v;
        temp->weight = edge.weight;
        temp->next = M[edge.u];
        M[edge.u] = temp;
    }

    temp = (Vertex) malloc(sizeof(struct node));

    if(temp != NULL) {
        temp->label = edge.u;
        temp->weight = edge.weight;
        temp->next = M[edge.v];
        M[edge.v] = temp;
    }
}

void displayList(AdjList M) {
    for(int i = 0; i < MAX; i++) {
        printf("Node %d: ", i);
        for(Vertex curr = M[i]; curr != NULL; curr = curr->next) {
            printf("%d ", curr->label);
        }
        printf("\n");
    }
}

void minHeapify(MinHeapList *L, int parent) {
    int smallest = parent;
    int left = parent * 2 + 1;
    int right = left + 1;

    if(left <= L->lastNdx && L->edges[left].weight < L->edges[smallest].weight) {
        smallest = left;
    }

    if(right <= L->lastNdx && L->edges[right].weight < L->edges[smallest].weight) {
        smallest = right;
    }

    if(smallest != parent) {
        EdgeType temp = L->edges[smallest];
        L->edges[smallest] = L->edges[parent];
        L->edges[parent] = temp;

        minHeapify(L, smallest);
    }
}

void insertMinHeap(MinHeapList *L, EdgeType edge) {
    if(L->lastNdx + 1 < MAX_SIZE) {
        int child = ++L->lastNdx;
        int parent = (child - 1) / 2;

        while(child > 0 && L->edges[parent].weight > edge.weight) {
            L->edges[child] = L->edges[parent];
            child = parent;
            parent = (child - 1) / 2;
        }

        L->edges[child] = edge;
    }
}

EdgeType deleteMin(MinHeapList *L) {
    EdgeType ret = {-1, -1, -1};

    if(L->lastNdx >= 0) {
        ret = L->edges[0];
        
        L->edges[0] = L->edges[L->lastNdx--];
        
        minHeapify(L, 0);
    }

    return ret;
}

void displayMinHeap(MinHeapList PQ) {
    for(int i = 0; i <= PQ.lastNdx; i++) {
        printf("%d ", PQ.edges[i].weight);
    }
    printf("\n");
}

void displayEdges(MST P) {
    while (P.eList.lastNdx >= 0) {
        EdgeType edge = deleteMin(&P.eList);
        printf("(%d, %d) = %d\n", edge.u, edge.v, edge.weight);
    }
}