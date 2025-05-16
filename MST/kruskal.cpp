#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



// Disjoint Set Union (DSU) with path compression and union by size
class DisjointSet {
private:
    // If Set[i] < 0, i is root with size -Set[i]; else Set[i] is parent
    vector<int> Set; 
public:
    // Constructor: initializes n disjoint sets
    DisjointSet(int n) {
        // Each element is initially its own root, size = 1
        Set.resize(n, -1);   
    }

    // Find with path compression
    int find(int x) {
        if (Set[x] < 0) return x;          // x is a root
        return Set[x] = find(Set[x]);      // path compression
    }

    // Union by size
    bool unionSets(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;          // already connected

        if (-Set[x] >= -Set[y]) {
            Set[x] += Set[y];              // update size
            Set[y] = x;                    // make x the parent
        } 
        else {
            Set[y] += Set[x];
            Set[x] = y;
        }
        return true;
    }
    
    // Get size of the set containing x
    int size(int x) {
        return -Set[find(x)];
    }

    // Print internal Set array
    void printSet() {
        cout << "Set array: ";
        for (int val : Set)
            cout << val << " ";
        cout << endl;
    }
};

// Edge structure: (u, v, weight)
struct Edge {
    int u, v, weight;
};


// Kruskal’s algorithm 
int kruskal(int V, vector<Edge>& edges, vector<Edge>& mstEdges) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    DisjointSet ds(V);
    int totalWeight = 0, count = 0;

    for (const Edge& e : edges) {
        if (ds.unionSets(e.u, e.v)) {
            mstEdges.push_back(e);
            totalWeight += e.weight;
            if (++count == V - 1) break; // MST complete
        }
    }

    return totalWeight;
}

int main() {
    int V = 6; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 4},
        {0, 2, 4},
        {1, 2, 2},
        {1, 3, 5},
        {2, 3, 8},
        {2, 4, 10},
        {3, 4, 2},
        {3, 5, 6},
        {4, 5, 3}
    };

    vector<Edge> mstEdges;
    int totalWeight = kruskal(V, edges, mstEdges);

    cout << "Minimum Spanning Tree edges:\n";
    for (const Edge& e : mstEdges)
        cout << e.u << " - " << e.v << " : " << e.weight << endl;

    cout << "Total weight of MST: " << totalWeight << endl;
    return 0;
}