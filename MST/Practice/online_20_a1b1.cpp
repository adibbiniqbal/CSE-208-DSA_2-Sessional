#include <iostream>
#include <vector>
#include <algorithm>
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
    int u, v, weight;
};

// Kruskal’s algorithm
int kruskal(int V, vector<Edge> &edges)
{
    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
        { return a.weight < b.weight; });

    DisjointSet ds(V);
    int totalWeight = 0, count = 0;

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
    int n;
    cin >> n;
    int house[n][2];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2; j++)
            cin >> house[i][j];
    }
    vector<Edge> edges;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                edges.push_back({i, j, (abs(house[i][0] - house[j][0]) + abs(house[i][1] - house[j][1]))});
                edges.push_back({j, i, (abs(house[i][0] - house[j][0]) + abs(house[i][1] - house[j][1]))});
            }
        }
    }
    int minCost = kruskal(n, edges);
    cout << minCost << endl;
}