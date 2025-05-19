#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

// Disjoint Set Union (DSU) with path compression and union by size
class DisjointSet
{
private:
    // If Set[i] < 0, i is root with size -Set[i]; else Set[i] is parent
    vector<int> Set;

public:
    // Constructor: initializes n disjoint sets
    DisjointSet(int n)
    {
        // Each element is initially its own root, size = 1
        Set.resize(n, -1);
    }

    // Find with path compression
    int find(int x)
    {
        if (Set[x] < 0)
            return x;                 // x is a root
        return Set[x] = find(Set[x]); // path compression
    }

    // Union by size
    bool unionSets(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false; // already connected

        if (-Set[x] >= -Set[y])
        {
            Set[x] += Set[y]; // update size
            Set[y] = x;       // make x the parent
        }
        else
        {
            Set[y] += Set[x];
            Set[x] = y;
        }
        return true;
    }

    // Get size of the set containing x
    int size(int x)
    {
        return -Set[find(x)];
    }

    // Print internal Set array
    void printSet()
    {
        cout << "Set array: ";
        for (int val : Set)
            cout << val << " ";
        cout << endl;
    }
};

// Edge structure: (u, v, weight)
struct Edge
{
    int u, v;
    float weight;
};

// Kruskal’s algorithm
float kruskal(int V, vector<Edge> &edges)
{
    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
        { return a.weight < b.weight; });

    DisjointSet ds(V);
    float totalWeight = 0;
    int count = 0;

    for (const Edge &e : edges)
    {
        if (ds.unionSets(e.u, e.v))
        {
            // mstEdges.push_back(e);
            totalWeight += e.weight;
            if (++count == V - 1)
                break; // MST complete
        }
    }

    return totalWeight;
}

int main()
{
    int n, m;
    float q;
    cin >> n >> m >> q;
    vector<Edge> edges;

    while (m--)
    {
        int u, v;
        float w;
        cin >> u >> v >> w;
        if(w>q){
            edges.push_back({u, v, q});
            edges.push_back({v, u, q});
        }
        else{
            edges.push_back({u, v, w});
            edges.push_back({v, u, w});
        }
        
    }
    float minCost = kruskal(n, edges);
    cout << fixed << setprecision(2) << minCost << endl;
    return 0;
}