#include <bits/stdc++.h>
using namespace std;

#include "../src/dsu.cpp"

int main() {
    // 5 elements: 0, 1, 2, 3, 4
    DSU dsu(5);

    // initially all separate
    cout << "find(0): " << dsu.find(0) << "\n";  // 0
    cout << "find(1): " << dsu.find(1) << "\n";  // 1

    // join 0 and 1
    cout << "join(0,1): " << dsu.join(0, 1) << "\n";  // 1 (success)
    cout << "find(0) == find(1): " << (dsu.find(0) == dsu.find(1)) << "\n";  // 1

    // join 2 and 3
    dsu.join(2, 3);
    cout << "find(2) == find(3): " << (dsu.find(2) == dsu.find(3)) << "\n";  // 1

    // 4 is still separate
    cout << "find(0) == find(4): " << (dsu.find(0) == dsu.find(4)) << "\n";  // 0
    cout << "find(2) == find(4): " << (dsu.find(2) == dsu.find(4)) << "\n";  // 0

    // join the two groups via 1 and 2
    dsu.join(1, 2);
    cout << "after join(1,2):\n";
    cout << "  find(0) == find(3): " << (dsu.find(0) == dsu.find(3)) << "\n";  // 1

    // joining same group returns false
    cout << "join(0,3): " << dsu.join(0, 3) << "\n";  // 0 (already same)

    // join 4 to the group
    dsu.join(4, 0);
    cout << "after join(4,0), all same group:\n";
    for (int i = 0; i < 5; i++)
        cout << "  find(" << i << "): " << dsu.find(i) << "\n";

    return 0;
}
