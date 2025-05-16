#include <iostream>
#include <vector>
using namespace std;

class DisjointSet {
private:
    vector<int> Set;

public:
    DisjointSet(int n) {
        Set.resize(n, -1); // Each element is initially its own root, size = 1
    }

    // Find with path compression
    int find(int x) {
        if (Set[x] < 0) return x;       // x is root
        return Set[x] = find(Set[x]);   // path compression
    }

    // Union by size without using swap and with minimal variables
    void unionSets(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;

        if (-Set[x] >= -Set[y]) {
            Set[x] += Set[y]; // update size
            Set[y] = x;       // make x the parent
        } else {
            Set[y] += Set[x];
            Set[x] = y;
        }
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

int main() {
    DisjointSet ds(7);

    ds.unionSets(0, 1);
    ds.unionSets(1, 2);
    ds.unionSets(3, 4);
    ds.unionSets(5, 6);
    ds.unionSets(4, 5);
    ds.unionSets(2, 6);

    ds.printSet();

    cout << "Size of set containing 0: " << ds.size(0) << endl;
    cout << "Find(4): " << ds.find(4) << endl;

    return 0;
}