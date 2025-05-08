#include <iostream>
using namespace std;

// Graph - Adjacency List
class Node {
private:
    int vertex;
    Node* next;

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
        // Insert v at the beginning of u's list
        Node* newNode = new Node(v);
        newNode->next = adjList[u];
        adjList[u] = newNode;

        // Since the graph is undirected, insert u in v's list
        newNode = new Node(u);
        newNode->next = adjList[v];
        adjList[v] = newNode;
    }

    // DFS using iterative approach with a stack; also builds the DFS tree.
    void DFS(int startVertex) {
        // Arrays to track visited nodes and parent relationships.
        bool* visited = new bool[vertices];
        int* parent = new int[vertices];
        for (int i = 0; i < vertices; i++) {
            visited[i] = false;
            parent[i] = -1;  // -1 indicates no parent (or root)
        }

        // Stack for iterative DFS.
        int* stack = new int[vertices];
        int top = -1;
        stack[++top] = startVertex;

        cout << "Depth-First Search starting from vertex " << startVertex << ": ";

        // Perform DFS.
        while (top >= 0) {
            int current = stack[top--];
            if (!visited[current]) {
                visited[current] = true;
                cout << current << " ";
                // Explore all neighbors of current.
                for (Node* temp = adjList[current]; temp != nullptr; temp = temp->next) {
                    int neighbor = temp->vertex;
                    // If neighbor hasn't been visited and no parent has been set (except for start),
                    // mark current as its parent.
                    if (!visited[neighbor] && parent[neighbor] == -1 && neighbor != startVertex) {
                        parent[neighbor] = current;
                    }
                    // Push neighbor onto stack if not visited.
                    if (!visited[neighbor]) {
                        stack[++top] = neighbor;
                    }
                }
            }
        }
        cout << "\n\n";

        // Build the DFS tree as an adjacency list from the parent array.
        Node** tree = new Node*[vertices];
        for (int i = 0; i < vertices; i++) {
            tree[i] = nullptr;
        }
        // For every vertex (except the start vertex), add it as a child of its parent.
        for (int i = 0; i < vertices; i++) {
            if (parent[i] != -1) {
                Node* newChild = new Node(i);
                newChild->next = tree[parent[i]];
                tree[parent[i]] = newChild;
            }
        }

        // Print the DFS tree in adjacency list format.
        cout << "DFS Tree (Adjacency List Representation):\n";
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

        // Cleanup dynamically allocated memory.
        for (int i = 0; i < vertices; i++) {
            Node* temp = tree[i];
            while (temp) {
                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        delete[] tree;
        delete[] visited;
        delete[] stack;
        delete[] parent;
    }

    ~Graph() {
        // Clean up the main adjacency list.
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

    g.DFS(0);

    return 0;
}
