#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define INF 9999

typedef struct {
    int u, v;
    int weight;
} EdgeType;

typedef struct node {
    EdgeType edge;
    struct node *next;
} *EdgeList;

typedef struct {
    EdgeList nodes;
    int totalWeight;
} MinimumCostTree;

typedef int AdjMatrix[MAX][MAX];

EdgeList createEdgeList(AdjMatrix M);
MinimumCostTree kruskals(AdjMatrix M);
void displayEdgeList(EdgeList edges);

void initMatrix(AdjMatrix M);
void insertEdge(AdjMatrix M, int edge[3]);
void displayMatrix(AdjMatrix M);
void displayEdges(AdjMatrix M);

int main() {
    int edges[][3] = {
        {0, 1, 2},  // Edge from 0 to 1 with weight 2
        {0, 2, 4},  // Edge from 0 to 2 with weight 4
        {1, 2, 1},  // Edge from 1 to 2 with weight 1
        {1, 3, 7},  // Edge from 1 to 3 with weight 7
        {2, 4, 3},  // Edge from 2 to 4 with weight 3
        {4, 3, 2}   // Edge from 4 to 3 with weight 2
    };

    int numOfEdges = sizeof(edges) / sizeof(edges[0]);
    
    AdjMatrix M;
    initMatrix(M);

    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(M, edges[i]);
    }

    displayMatrix(M);

    MinimumCostTree MCT = kruskals(M);
    printf("Minimum weight is: %d\n", MCT.totalWeight);

    printf("MCT Edges: ");
    displayEdgeList(MCT.nodes);

    return 0;
}

// specific to undirected graph only
EdgeList createEdgeList(AdjMatrix M) {
    EdgeList edges = NULL;

    for(int i = 0; i < MAX; i++) {
        for(int j = i + 1; j < MAX; j++) {
            if(M[i][j] != INF) {
                EdgeType e = {i, j, M[i][j]};

                EdgeList temp = (EdgeList) malloc(sizeof(struct node));

                if(temp != NULL) {
                    EdgeList *trav;
                    
                    for(trav = &edges; (*trav) != NULL && (*trav)->edge.weight < e.weight; trav = &(*trav)->next) {}

                    temp->edge = e;
                    temp->next = *trav;
                    *trav = temp;
                }
            }
        }
    }

    return edges;
}

MinimumCostTree kruskals(AdjMatrix M) {
    MinimumCostTree MCT = {NULL, 0};
    int treeGroup[MAX];

    // initialize treeGroup
    for(int i = 0; i < MAX; i++) {
        treeGroup[i] = i;
    }

    EdgeList edges = createEdgeList(M);

    while(edges != NULL) {
        EdgeList temp = edges;
        edges = edges->next;

        int u = temp->edge.u;
        int v = temp->edge.v;
        
        if(treeGroup[u] != treeGroup[v]) {
            MCT.totalWeight += temp->edge.weight;

            // temporarily store the tree label to be changed
            int change = treeGroup[u];

            for(int i = 0; i < MAX; i++) {
                if(treeGroup[i] == change) {
                    treeGroup[i] = treeGroup[v];
                }
            }

            temp->next = MCT.nodes;
            MCT.nodes = temp;
        }
        else {
            free(temp);
        }
    }

    return MCT;
}

void displayEdgeList(EdgeList edges) {
    for(; edges != NULL; edges = edges->next) {
        printf("[(%d, %d) = %d] ", edges->edge.u, edges->edge.v, edges->edge.weight);
    }
}

void initMatrix(AdjMatrix M) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            M[i][j] = INF;
        }
    }
}

void insertEdge(AdjMatrix M, int edge[3]) {
    M[edge[0]][edge[1]] = edge[2];
    M[edge[1]][edge[0]] = edge[2];
}

void displayMatrix(AdjMatrix M) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            (M[i][j] == INF) ? printf("INF ") : printf("%3d ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void displayEdges(AdjMatrix M) {
    printf("Edges: ");
    for(int i = 0; i < MAX; i++) {
        for(int j = i + 1; j < MAX; j++) {
            if(M[i][j] == 1) {
                printf("(%d, %d) ", i, j);
            }
        }
    }
}