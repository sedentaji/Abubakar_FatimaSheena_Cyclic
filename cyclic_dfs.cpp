#include <iostream>
#include <vector>
#include <stack>
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
    
    // DFS helper function for cycle detection
    bool dfsUtil(int v, vector<int>& color, vector<int>& path, vector<int>& cycleVertices) {
        color[v] = 1; // Gray (currently being processed)
        path.push_back(v);
        
        for (int u = 0; u < vertices; u++) {
            if (adjMatrix[v][u] == 1) { // There's an edge from v to u
                if (color[u] == 1) { // Back edge found - cycle detected
                    // Build cycle path from u to the end of current path
                    cycleVertices.clear();
                    bool foundStart = false;
                    for (int i = 0; i < path.size(); i++) {
                        if (path[i] == u) {
                            foundStart = true;
                        }
                        if (foundStart) {
                            cycleVertices.push_back(path[i]);
                        }
                    }
                    cycleVertices.push_back(u); // Complete the cycle
                    return true;
                }
                
                if (color[u] == 0) { // White (unvisited)
                    if (dfsUtil(u, color, path, cycleVertices)) {
                        return true;
                    }
                }
            }
        }
        
        color[v] = 2; // Black (completely processed)
        path.pop_back();
        return false;
    }
    
    // Main DFS cycle detection function
    bool detectCycleDFS() {
        vector<int> color(vertices, 0); // 0: White, 1: Gray, 2: Black
        vector<int> path;
        vector<int> cycleVertices;
        
        cout << "\n=== DFS CYCLE DETECTION ===\n";
        
        for (int i = 0; i < vertices; i++) {
            if (color[i] == 0) {
                if (dfsUtil(i, color, path, cycleVertices)) {
                    cout << "CYCLE DETECTED!\n";
                    cout << "Vertices in the cycle: ";
                    for (int j = 0; j < cycleVertices.size(); j++) {
                        cout << cycleVertices[j];
                        if (j < cycleVertices.size() - 1) cout << " -> ";
                    }
                    cout << "\n";
                    return true;
                }
            }
        }
        
        cout << "NO CYCLE DETECTED\n";
        return false;
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
    
    cout << "=== GRAPH CYCLE DETECTION USING DFS ===\n";
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    
    if (vertices <= 0) {
        cout << "Invalid number of vertices!\n";
        return 1;
    }
    
    Graph graph(vertices);
    graph.inputMatrix();
    graph.displayMatrix();
    
    bool hasCycle = graph.detectCycleDFS();
    
    cout << "\nResult: The graph is " << (hasCycle ? "CYCLIC" : "ACYCLIC") << "\n";
    
    return 0;
}