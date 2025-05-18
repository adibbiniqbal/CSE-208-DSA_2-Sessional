#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
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
int kruskal(DisjointSet &ds, int V, vector<Edge> &edges, vector<Edge> &mstEdges, vector<int> &risky)
{
    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
        { return a.weight < b.weight; });

    int totalWeight = 0;

    for (const Edge &e : edges)
    {
        if (ds.unionSets(e.u, e.v))
        {
            mstEdges.push_back(e);
            totalWeight += e.weight;
            bool complete = true;
            set<int> st;
            for (int i = 0; i < V; i++)
            {
                if (risky[i])
                    continue;
                st.insert(ds.find(i));
                if (st.size() > 1)
                {
                    complete = false;
                    break;
                }
            }
            if (complete)
                break;
        }
    }

    return totalWeight;
}

int main()
{
    int N, M, P, k;
    cin >> N >> M >> P >> k;
    vector<int> risky(N, 0);
    for (int i = 0; i < k; i++)
    {
        int r;
        cin >> r;
        risky[r] = 1;
    }
    vector<Edge> edges;
    vector<Edge> riskyEdges;
    while (M--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        if (risky[u] == 0 && risky[v] == 0)
        {
            edges.push_back({u, v, w});
            edges.push_back({v, u, w});
        }
        else
        {
            riskyEdges.push_back({u, v, w + (risky[u] + risky[v]) * P});
            riskyEdges.push_back({v, u, w + (risky[u] + risky[v]) * P});
        }
    }
    if (N - k == 0)
    {
        cout << endl
            << 0 << endl
            << 0 << endl;
        return 0;
    }
    vector<Edge> mstEdges;
    DisjointSet ds(N);
    int totalWeight = kruskal(ds, N, edges, mstEdges, risky);
    bool complete = true;
    set<int> st;
    for (int i = 0; i < N; i++)
    {
        if (risky[i])
            continue;
        st.insert(ds.find(i));
        if (st.size() > 1)
        {
            complete = false;
            break;
        }
    }
    if (!complete)
    {
        totalWeight += kruskal(ds, N, riskyEdges, mstEdges, risky);
    }
    cout << endl;
    cout << mstEdges.size() << endl;
    for (const Edge &e : mstEdges)
        cout << e.u << " " << e.v << endl;

    cout << totalWeight << endl;
    return 0;
}