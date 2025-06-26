#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <time.h>  // Include time.h for randomization 
#define MAX 100  //  Define the maximum number of vertices 
 
// Structure to represent a graph using an adjacency matrix 
typedef struct { 
    int V;          // Number of vertices 
    int adj[MAX][MAX];  // Adjacency matrix 
} Graph; 
 
// Function to create a graph with V vertices 
Graph* createGraph(int V) { 
    Graph* graph = (Graph*) malloc(sizeof(Graph));  // Allocate memory for the graph 
    graph->V = V;  // Set the number of vertices 
    for (int i = 0; i < V; i++) { 
        for (int j = 0; j < V; j++) { 
            graph->adj[i][j] = 0;  // Initialize the adjacency matrix with 0s 
        } 
    } 
    return graph;  // Return the created graph 
} 
 
// Function to add an edge to the graph 
void addEdge(Graph* graph, int src, int dest) { 
    graph->adj[src][dest] = 1;  // Add edge from src to dest 
    graph->adj[dest][src] = 1;  // Since the graph is undirected, add edge from dest to src 
    printf("Edge added between vertices %d and %d\n", src, dest); 
}

// Function to perform BFS traversal from a given source vertex 
void BFS(Graph* graph, int startVertex) { 
    bool visited[MAX] = { false };  // Array to keep track of visited vertices 
    int queue[MAX];  // Array to implement the queue 
    int front = 0, rear = 0;  // Front and rear indices of the queue 
 
    visited[startVertex] = true;  // Mark the start vertex as visited 
    queue[rear++] = startVertex;  // Enqueue the start vertex 
 
    while (front != rear) {   // Loop until the queue is empty 
        int currentVertex = queue[front++];   // Dequeue a vertex 
        printf("Visited %d\n", currentVertex);  // Print the visited vertex 
 
        // Traverse the adjacency matrix of the current vertex 
        for (int i = 0; i < graph->V; i++) { 
            if (graph->adj[currentVertex][i] && !visited[i]) { 
                visited[i] = true;  // Mark the adjacent vertex as visited 
                queue[rear++] = i;  // Enqueue the adjacent vertex 
            } 
        } 
    } 
} 
 
// Utility function for DFS traversal 
void DFSUtil(Graph* graph, int vertex, bool visited[]) { 
    visited[vertex] = true;  // Mark the current vertex as visited 
    printf("Visited %d\n", vertex);  // Print the visited vertex 
 
    // Traverse the adjacency matrix of the current vertex 
    for (int i = 0; i < graph->V; i++) { 
        if (graph->adj[vertex][i] && !visited[i]) { 
            DFSUtil(graph, i, visited);  // Recursively visit the adjacent vertex
             } 
    } 
} 
 
// Function to perform DFS traversal from a given source vertex 
void DFS(Graph* graph, int startVertex) { 
    bool visited[MAX] = { false };  // Array to keep track of visited vertices 
    DFSUtil(graph, startVertex, visited);  // Call the utility function to start DFS 
} 
 
// Main function to test BFS and DFS 
int main() { 
    srand(time(NULL));  // Seed the random number generator with current time 
    int V = 6;  // Number of vertices in the graph 
    Graph* graph = createGraph(V);  // Create the graph 
 
    printf("Randomly generated edges:\n"); 
    // Add random edges to the graph 
    for (int i = 0; i < V; i++) { 
        for (int j = i + 1; j < V; j++) { 
            if (rand() % 2 == 1) {  // Randomly decide whether to add an edge between vertices i 
and j 
                addEdge(graph, i, j); 
            } 
        } 
    } 
 
    printf("\nBreadth First Traversal starting from vertex 0:\n"); 
    BFS(graph, 0);  // Perform BFS starting from vertex 0 
 
    printf("\nDepth First Traversal starting from vertex 0:\n"); 
    DFS(graph, 0);  // Perform DFS starting from vertex 0 
free(graph);  // Free the allocated graph 
return 0;  // Return 0 to indicate successful execution 
}