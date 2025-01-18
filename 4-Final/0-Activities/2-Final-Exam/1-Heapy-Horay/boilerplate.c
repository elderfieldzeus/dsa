#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    char name[100];  // Task name
    int duration;    // Task duration (in minutes)
} Task;

typedef struct {
    Task* heap;      // Dynamic array for the heap
    int size;        // Number of elements in the heap
    int capacity;    // Capacity of the heap
} MinHeap;

// Function prototypes
void heapify(MinHeap* pq, int i);
void insert(MinHeap* pq, Task task);
Task extractMin(MinHeap* pq);
void display(MinHeap* pq);
void resizeHeap(MinHeap* pq);

int main() {
    MinHeap pq;
    pq.size = 0;
    pq.capacity = 2;  // Initial capacity
    pq.heap = (Task*)malloc(pq.capacity * sizeof(Task));  // Allocate memory for heap

    if (pq.heap == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    int numTasks;
    printf("Enter the number of tasks: ");
    scanf("%d", &numTasks);

    // Inserting tasks dynamically
    for (int i = 0; i < numTasks; i++) {
        Task task;
        printf("Enter task %d name: ", i + 1);
        getchar();  // To clear the buffer before reading a string
        fgets(task.name, sizeof(task.name), stdin);
        task.name[strcspn(task.name, "\n")] = 0;  // Remove trailing newline
        printf("Enter duration for task %d (in minutes): ", i + 1);
        scanf("%d", &task.duration);

        insert(&pq, task);
    }

    printf("\nPriority Queue after insertions:\n");
    display(&pq);

    // Extracting all tasks until the queue is empty and displaying after each removal
    printf("\nExtracting tasks in order of priority:\n");
    while (pq.size > 0) {
        Task minTask = extractMin(&pq);
        printf("Extracted Task: %s, Duration: %d\n", minTask.name, minTask.duration);

        // Display remaining tasks after extraction
        printf("\nPriority Queue after removal:\n");
        display(&pq);
    }

    printf("\nPriority Queue is now empty.\n");

    // Free dynamically allocated memory
    free(pq.heap);

    return 0;
}

// Function to maintain the heap property by heapifying the subtree rooted at index i
void heapify(MinHeap* pq, int i) {
    // To do code logic here
    
}


// Healper function taht can be used.
// Function to resize the heap array dynamically when it gets full
void resizeHeap(MinHeap* pq) {
    pq->capacity *= 2;
    pq->heap = (Task*)realloc(pq->heap, pq->capacity * sizeof(Task));
    if (pq->heap == NULL) {
        printf("Memory allocation failed!\n");
        exit(-1);
    }
}

// Function to insert a task into the priority queue
void insert(MinHeap* pq, Task task) {
    if (pq->size >= pq->capacity) {
        resizeHeap(pq);  // Resize the heap if it is full
    }

    pq->heap[pq->size] = task;
    pq->size++;

    // Fix the min-heap property by bubbling up
    int i = pq->size - 1;
    while (i > 0 && pq->heap[(i - 1) / 2].duration > pq->heap[i].duration) {
        Task temp = pq->heap[i];
        pq->heap[i] = pq->heap[(i - 1) / 2];
        pq->heap[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

// Function to extract the task with the minimum duration
Task extractMin(MinHeap* pq) {
    if (pq->size == 0) {
        printf("Heap is empty!\n");
        Task emptyTask = {"", -1};
        return emptyTask;
    }

    Task minTask = pq->heap[0];

    // Move the last task to the root and reduce heap size
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;

    // Heapify the root to restore heap property
    heapify(pq, 0);

    return minTask;
}

// Function to display the tasks in the priority queue
void display(MinHeap* pq) {
    if (pq->size == 0) {
        printf("Priority Queue is empty!\n");
        return;
    }

    for (int i = 0; i < pq->size; i++) {
        printf("Task: %s, Duration: %d\n", pq->heap[i].name, pq->heap[i].duration);
    }
}