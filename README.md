# dsa
<div align="center">
   <h3>repository for my DSA code wahah !!</h3>
   <p>feel free to steal or whatever haha</p>
   <img src="./etc/lol-spongebob.gif" width="500">
</div>

<hr />

# Table of Contents
- [Pre-Midterm Topics](#pre-midterm-topics)
- [Midterm Topics](#midterm-topics)
- [Pre-Final Topics](#pre-final-topics)
- [Final Topics](#final-topics)

# Coverage

## Pre-Midterm Topics

1. **Abstract Data Type (ADT)**

2. **ADT List**
   - Differentiate a List from an ADT List.
   - List Operations: Initialize, insert, delete, member, locate, and other operations
   - Implementations of ADT List:
     1. **Array Implementation (4 versions)**
        - **Version 1**: List is a structure containing an array and variable count  
          *Note*: count represents the actual number of elements in the array  
          - If MAX is the size of the array, count <= MAX
        - **Version 2**: List is a pointer to a structure containing an array and variable count
        - **Version 3**: List is a structure containing a pointer to the 1st element of a dynamic array, and variable count
        - **Version 4**: List is a pointer to a structure containing a pointer to the 1st element of a dynamic array, and variable count
     2. **Linked List Implementation (Singly Link)**
     3. **Cursor-based Implementation**
   - Time Complexity of the List operations in different implementations: O(1), O(N), and O(N\*N)

3. **ADT Stack and Implementations**
   - What is an ADT Stack?
   - Stack Operations: Top, Pop, Push, and other utility functions such as initStack, isEmpty, and isFull
   - Implementations
     1. **Array Implementation (4 versions)**
     2. **Linked List Implementation**
     3. **Cursor-based Implementation**
   - Time Complexity: O(1) and O(N)

4. **ADT Queue and Implementations**
   - What is an ADT Queue?
   - Queue Operations: Front, Dequeue, Enqueue, and other utility functions such as initQueue, isEmpty, and isFull
   - Implementations
     1. **Linked List Implementation**
        - **Queue is a pointer to a dynamically allocated node**
        - **Queue is a structure containing front and rear pointers to dynamically allocated node/s**
     2. **Circular Array Implementation**
        - **Solution 1**: Add a counter
        - **Solution 2**: Queue is full if there are MAX-1 elements  
          *Note*: where MAX is the size of the array
   - Time Complexity: O(1) and O(N)

**Caution**: The Stack and the Queue **CANNOT be traversed**! (See definition of stack and queue)

## Midterm Topics

1. **Set and ADT Set**
   - ADT Set vs. ADT List
   - What are the differences between the two?
   - ADT's based on Set
     1. **ADT UID**
        - An ADT based on set with operations Union, Intersection, and set Difference
        - Implementations
          1. Array, Linked list, and cursor-based implementations
          2. Bit-Vector Implementation
          3. Computer Word Implementation
             - Shift operators: `>>` and `<<`
             - Bit-wise operators: `&` `^` `|` `~`

2. **ADT Dictionary**
   - An ADT based on set with operations Insert, Delete, and Member
   - Two types of Hashing:
     1. Open Hashing (or External Hashing)
     2. Closed Hashing (or Internal Hashing)

   - *Closed Hashing Terms*: Collision, Synonyms, Linear Hashing or Probing, Displacement, Packing Density (Load Factor), Average Search Length, Perfect Hash Function
   - Closed Hashing variants
     - Closed Hashing in external Memory (Files: fopen, fclose, fread, fwrite, fseek)

## Pre-Final Topics

1. **ADT Tree and Implementations** [Source: Data Structure by Aho, Hopcroft, and Ullman]
   - Definition of a tree
   - Basic concepts and terms related to tree
   - Tree Traversals [Preorder, Inorder, Postorder]
   - ADT Tree Implementations
     - Parent Pointer Implementation
     - List of Children Implementation
   - Binary Tree definition and Implementations
   - Expression Trees
   - Huffman Code

2. **Binary Search Tree (BST)** [Sources: There are many sites on the internet such as Geeks for Geeks]
   - Description and Implementation
   - Operations: Insert, Delete, and Member
   - Similarity and Difference between BST and AVL trees
   - Binary Search vs. Sequential Search

3. **ADT Priority Queue**
   - Partially Ordered Tree (POT)
   - Min and Max heap
     - **MinHeap**: Operations: insert and deleteMin [Source: Data Structure by Aho, Hopcroft, and Ullman]
     - **MaxHeap**: Operations: insert and deleteMax [Sources: Internet]
     - MinHeapify and MaxHeapify
       - **Version 1**: Insert all elements in an initially empty POT [Source: ebook]
       - **Version 2**: Heapify starting with lowest level parent [Sources: Internet]

4. **Heapsort Sorting Technique (in place)**
   - A sorting algorithm is an "in place" sorting algorithm if there is no additional array used when implementing the sorting process.

## Final Topics

1. **Directed and Undirected Graph** [Source: Data Structure by Aho, Hopcroft, and Ullman]
   - Concepts
   - Graph Implementations:
     1. Adjacency Matrix
     2. Adjacency List 
2. **Graph Algorithms** [Source: Data Structure by Aho, Hopcroft, and Ullman]
    -  Shortest Paths: Dijkstra's Floyd's, and Warshall's Algorithms
    -  Traversals: Depth First Search (DFS) and Breadth First Search (BFS)
    -  Minimum Cost Spanning Tree: Prim's and Kruskal's Algorithms
