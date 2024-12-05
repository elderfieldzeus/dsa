#include <stdio.h>
#include <stdlib.h>
#define MAX 6
#define MAX_SIZE 20
#define infinity 999

typedef int Vertex;

typedef int LabelAdjMat[MAX][MAX];

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

MST Kruskals(LabelAdjMat M);

void initMatrix(LabelAdjMat M);
void insertEdge(LabelAdjMat M, EdgeType edge);
void minHeapify(MinHeapList *L, int parent);
void insertMinHeap(MinHeapList *L, EdgeType edge);
EdgeType deleteMin(MinHeapList *L);
MinHeapList createMinHeap(LabelAdjMat M);
void displayMinHeap(MinHeapList PQ);

void displayEdges(MST K);


int main() {
    LabelAdjMat M;
    initMatrix(M);

    
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


    MST K = Kruskals(M);
    printf("Minimum weight is %d.\n", K.cost);
    displayEdges(K);

    return 0;
}

MST Kruskals(LabelAdjMat M) {
    MST K = {{.lastNdx = -1}, 0};
    MinHeapList PQ = createMinHeap(M);

    int Comp[MAX];

    for(int i = 0; i < MAX; i++) {
        Comp[i] = i;
    }

    while(PQ.lastNdx >= 0) {
        EdgeType min = deleteMin(&PQ);

        if(Comp[min.u] != Comp[min.v]) {
            int change = Comp[min.u];

            for(int i = 0; i < MAX; i++) {
                if (Comp[i] == change) {
                    Comp[i] = Comp[min.v];
                }
            }

            insertMinHeap(&K.eList, min);
            K.cost += min.weight;
        }
    }

    return K;
}

void initMatrix(LabelAdjMat M) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            M[i][j] = infinity;
        }
    }
}

void insertEdge(LabelAdjMat M, EdgeType edge) {
    M[edge.u][edge.v] = edge.weight;
    M[edge.v][edge.u] = edge.weight;
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

MinHeapList createMinHeap(LabelAdjMat M) {
    MinHeapList PQ = {.lastNdx = -1};

    for(int i = 0; i < MAX; i++) {
        for(int j = i + 1; j < MAX; j++) {
            if(M[i][j] != infinity) {
                insertMinHeap(&PQ, (EdgeType){i, j, M[i][j]});
            }
        }
    }

    return PQ;
}

void displayMinHeap(MinHeapList PQ) {
    for(int i = 0; i <= PQ.lastNdx; i++) {
        printf("%d ", PQ.edges[i].weight);
    }
    printf("\n");
}

void displayEdges(MST K) {
    while (K.eList.lastNdx >= 0) {
        EdgeType edge = deleteMin(&K.eList);
        printf("(%d, %d) = %d\n", edge.u, edge.v, edge.weight);
    }
}