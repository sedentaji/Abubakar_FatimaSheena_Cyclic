#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjMatrix;
    
public:
    Graph(int v) : vertices(v) {
        adjMatrix.resize(v, vector<int>(v, 0));
    }
    
    // Function to input the adjacency matrix
    void inputMatrix() {
        cout << "Enter the adjacency matrix (" << vertices << "x" << vertices << "):\n";
        cout << "Enter 1 if there's an edge from vertex i to vertex j, 0 otherwise:\n";
        
        for (int i = 0; i < vertices; i++) {
            cout << "Row " << i << ": ";
            for (int j = 0; j < vertices; j++) {
                cin >> adjMatrix[i][j];
            }
        }
    }
    
    // BFS cycle detection using Kahn's algorithm (topological sorting)
    bool detectCycleBFS() {
        vector<int> inDegree(vertices, 0);
        vector<int> processedOrder;
        
        cout << "\n=== BFS CYCLE DETECTION ===\n";
        
        // Calculate in-degrees
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (adjMatrix[i][j] == 1) {
                    inDegree[j]++;
                }
            }
        }
        
        cout << "Initial in-degrees: ";
        for (int i = 0; i < vertices; i++) {
            cout << "V" << i << "(" << inDegree[i] << ") ";
        }
        cout << "\n";
        
        // Find all vertices with in-degree 0
        queue<int> q;
        for (int i = 0; i < vertices; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        int processedVertices = 0;
        
        cout << "\nBFS Processing:\n";
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            processedOrder.push_back(u);
            processedVertices++;
            
            cout << "Processing vertex " << u << "\n";
            
            // Reduce in-degree of adjacent vertices
            for (int v = 0; v < vertices; v++) {
                if (adjMatrix[u][v] == 1) {
                    inDegree[v]--;
                    cout << "  Reduced in-degree of vertex " << v << " to " << inDegree[v] << "\n";
                    
                    if (inDegree[v] == 0) {
                        q.push(v);
                        cout << "  Added vertex " << v << " to queue\n";
                    }
                }
            }
        }
        
        if (!processedOrder.empty()) {
            cout << "\nProcessing order: ";
            for (int i = 0; i < processedOrder.size(); i++) {
                cout << processedOrder[i];
                if (i < processedOrder.size() - 1) cout << " -> ";
            }
            cout << "\n";
        }
        
        cout << "Processed vertices: " << processedVertices << " out of " << vertices << "\n";
        
        if (processedVertices != vertices) {
            cout << "CYCLE DETECTED!\n";
            cout << "Unprocessed vertices (part of cycle): ";
            for (int i = 0; i < vertices; i++) {
                bool found = false;
                for (int j = 0; j < processedOrder.size(); j++) {
                    if (processedOrder[j] == i) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << i << " ";
                }
            }
            cout << "\n";
            return true;
        } else {
            cout << "NO CYCLE DETECTED\n";
            return false;
        }
    }
    
    // Display the adjacency matrix
    void displayMatrix() {
        cout << "\nAdjacency Matrix:\n";
        cout << "   ";
        for (int i = 0; i < vertices; i++) {
            cout << i << " ";
        }
        cout << "\n";
        
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            for (int j = 0; j < vertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    int vertices;
    
    cout << "=== GRAPH CYCLE DETECTION USING BFS ===\n";
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    
    if (vertices <= 0) {
        cout << "Invalid number of vertices!\n";
        return 1;
    }
    
    Graph graph(vertices);
    graph.inputMatrix();
    graph.displayMatrix();
    
    bool hasCycle = graph.detectCycleBFS();
    
    cout << "\nResult: The graph is " << (hasCycle ? "CYCLIC" : "ACYCLIC") << "\n";
    
    return 0;
}