#include <bits/stdc++.h>
using namespace std;

#include "../../src/graph/tarjan-scc.cpp"

int main() {
    /*
        Directed graph (0-indexed):
        0 -> 1 -> 2 -> 0  (SCC: {0,1,2})
        2 -> 3 -> 4 -> 3  (SCC: {3,4})
        4 -> 5            (SCC: {5})
    */
    TarjanSCC<10> scc;
    scc.n = 6;
    scc.add_edge(0, 1);
    scc.add_edge(1, 2);
    scc.add_edge(2, 0);
    scc.add_edge(2, 3);
    scc.add_edge(3, 4);
    scc.add_edge(4, 3);
    scc.add_edge(4, 5);

    int num = scc.build();
    cout << "Number of SCCs: " << num << "\n";  // 3

    cout << "same(0,1): " << scc.same(0, 1) << "\n";  // 1
    cout << "same(0,2): " << scc.same(0, 2) << "\n";  // 1
    cout << "same(3,4): " << scc.same(3, 4) << "\n";  // 1
    cout << "same(0,3): " << scc.same(0, 3) << "\n";  // 0
    cout << "same(4,5): " << scc.same(4, 5) << "\n";  // 0

    // print component IDs
    cout << "Component IDs: ";
    for (int i = 0; i < 6; i++) cout << scc.comp[i] << " ";
    cout << "\n";

    return 0;
}
