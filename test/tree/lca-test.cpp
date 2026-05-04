#include <bits/stdc++.h>
using namespace std;

#include "../../src/tree/lca.cpp"

int main() {
    /*
        Tree structure (1-indexed):
              1
             /|\
            2 3 4
           /|   |
          5 6   7
    */
    LCA<10> lca;
    lca.n = 7;
    lca.add_edge(1, 2);
    lca.add_edge(1, 3);
    lca.add_edge(1, 4);
    lca.add_edge(2, 5);
    lca.add_edge(2, 6);
    lca.add_edge(4, 7);
    lca.build(1);

    // LCA queries
    cout << "lca(5,6): " << lca.query(5, 6) << "\n";  // 2
    cout << "lca(5,7): " << lca.query(5, 7) << "\n";  // 1
    cout << "lca(5,3): " << lca.query(5, 3) << "\n";  // 1
    cout << "lca(6,2): " << lca.query(6, 2) << "\n";  // 2
    cout << "lca(4,7): " << lca.query(4, 7) << "\n";  // 4

    // distance queries
    cout << "dist(5,6): " << lca.dist(5, 6) << "\n";  // 2
    cout << "dist(5,7): " << lca.dist(5, 7) << "\n";  // 4
    cout << "dist(1,7): " << lca.dist(1, 7) << "\n";  // 2

    return 0;
}
