#include <iostream>
#include <vector>
using namespace std;

// The Bellman-Ford function as provided
vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    vector<int> dist(V, 1e8);
    dist[src] = 0;
    
    for (int i = 0; i < V - 1; i++) {
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            int wt = it[2];
            
            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }
    
    // Check for negative weight cycles
    for (auto it : edges) {
        int u = it[0];
        int v = it[1];
        int wt = it[2];
        
        if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
            return { -1 }; // Indicates a negative weight cycle
        }
    }
    
    return dist;
}

int main() {
    int V, E, src;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> edges;
    cout << "Enter the edges (u v weight) for each edge:\n";
    for (int i = 0; i < E; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        edges.push_back({u, v, wt});
    }
    
    cout << "Enter the source vertex: ";
    cin >> src;
    vector<int> distances = bellmanFord(V, edges, src);

    if (distances.size() == 1 && distances[0] == -1) {
        cout << "Graph contains a negative weight cycle.\n";
    } else {
        cout << "Shortest distances from source vertex " << src << ":\n";
        for (int i = 0; i < V; i++) {
            if (distances[i] == 1e8) {
                cout << "Vertex " << i << " is unreachable\n";
            } else {
                cout << "Vertex " << i << ": " << distances[i] << "\n";
            }
        }
    }

    return 0;
}

// Enter the number of vertices: 5
// Enter the number of edges: 8
// Enter the edges (u v weight) for each edge:
// 0 1 4
// 0 2 1
// 1 3 1
// 2 1 2
// 2 3 5
// 3 4 3
// 1 4 7
// 2 4 8
// Enter the source vertex: 0
// Shortest distances from source vertex 0:
// Vertex 0: 0
// Vertex 1: 3
// Vertex 2: 1
// Vertex 3: 4
// Vertex 4: 7