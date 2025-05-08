#include <iostream>
using namespace std;

// Graph - Adjacency List

class Node {
private:
    int vertex;
    Node* next;

    // Private constructor only accessible to friend class Graph
    Node(int v) : vertex(v), next(nullptr) {}

    friend class Graph;
};

class Graph {
private:
    int vertices;
    Node** adjList;

public:
    Graph(int v) {
        vertices = v;
        adjList = new Node*[v];
        for (int i = 0; i < v; i++) {
            adjList[i] = nullptr;
        }
    }

    void addEdge(int u, int v) {
        // Add edge from u to v
        Node* newNode = new Node(v);
        newNode->next = adjList[u];
        adjList[u] = newNode;

        // Add edge from v to u (undirected graph)
        newNode = new Node(u);
        newNode->next = adjList[v];
        adjList[v] = newNode;
    }

    // BFS that prints the order of traversal and builds/prints the BFS tree.
    void BFS(int startVertex) {
        // Array to track visited vertices
        bool* visited = new bool[vertices];
        // Array to store parent of each vertex in the BFS tree (-1 for root)
        int* parent = new int[vertices];
        for (int i = 0; i < vertices; i++) {
            visited[i] = false;
            parent[i] = -1;
        }

        // Queue implementation using a dynamic array
        int* queue = new int[vertices];
        int front = 0, rear = 0;

        // Start with the startVertex
        visited[startVertex] = true;
        queue[rear++] = startVertex;

        cout << "Breadth-First Search starting from vertex " << startVertex << ":\n";

        // Perform BFS traversal
        while (front < rear) {
            int current = queue[front++];
            cout << current << " ";

            // For each neighbor of current
            for (Node* temp = adjList[current]; temp != nullptr; temp = temp->next) {
                int neighbor = temp->vertex;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;  // Set the parent for BFS tree
                    queue[rear++] = neighbor;
                }
            }
        }
        cout << "\n\n";

        // Build the BFS tree as an adjacency list using the Node structure.
        // Each vertex's children in the BFS tree will be stored in tree[vertex].
        Node** tree = new Node*[vertices];
        for (int i = 0; i < vertices; i++) {
            tree[i] = nullptr;
        }

        // For each vertex (except the starting vertex), add it as a child of its parent.
        for (int i = 0; i < vertices; i++) {
            if (parent[i] != -1) {
                // Create a new node for vertex i
                Node* newChild = new Node(i);
                // Insert it at the beginning of the parent's child list
                newChild->next = tree[parent[i]];
                tree[parent[i]] = newChild;
            }
        }

        // Print the BFS tree as an adjacency list representation.
        cout << "BFS Tree (Adjacency List Representation):\n";
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            if (tree[i] == nullptr) {
                cout << "No children";
            } else {
                for (Node* temp = tree[i]; temp != nullptr; temp = temp->next) {
                    cout << temp->vertex << " ";
                }
            }
            cout << "\n";
        }

        // Cleanup: Free dynamically allocated memory for visited, parent, and queue.
        delete[] visited;
        delete[] parent;
        delete[] queue;

        // Free the BFS tree memory.
        for (int i = 0; i < vertices; i++) {
            Node* temp = tree[i];
            while (temp) {
                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        delete[] tree;
    }

    ~Graph() {
        // Cleanup the original adjacency list
        for (int i = 0; i < vertices; i++) {
            Node* temp = adjList[i];
            while (temp) {
                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        delete[] adjList;
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    g.BFS(0);

    return 0;
}
