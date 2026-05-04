#include <bits/stdc++.h>
using namespace std;

#include "../../src/tree/hld.cpp"

int main() {
    /*
        Tree structure (1-indexed):
              1
             /|\
            2 3 4
           /|   |
          5 6   7
    */
    HLD<10> hld;
    hld.n = 7;
    hld.add_edge(1, 2);
    hld.add_edge(1, 3);
    hld.add_edge(1, 4);
    hld.add_edge(2, 5);
    hld.add_edge(2, 6);
    hld.add_edge(4, 7);
    hld.build(1);

    // LCA queries
    cout << "lca(5,6): " << hld.lca(5, 6) << "\n";  // 2
    cout << "lca(5,7): " << hld.lca(5, 7) << "\n";  // 1
    cout << "lca(4,7): " << hld.lca(4, 7) << "\n";  // 4

    // path add: add 10 to path 5->7 (nodes: 5,2,1,4,7)
    hld.path_add(5, 7, 10);
    cout << "after path_add(5,7,10):\n";
    cout << "  val[5]: " << hld.point_query(5) << "\n";  // 10
    cout << "  val[2]: " << hld.point_query(2) << "\n";  // 10
    cout << "  val[1]: " << hld.point_query(1) << "\n";  // 10
    cout << "  val[4]: " << hld.point_query(4) << "\n";  // 10
    cout << "  val[7]: " << hld.point_query(7) << "\n";  // 10
    cout << "  val[3]: " << hld.point_query(3) << "\n";  // 0 (not on path)
    cout << "  val[6]: " << hld.point_query(6) << "\n";  // 0 (not on path)

    // path add: add 5 to path 5->6 (nodes: 5,2,6)
    hld.path_add(5, 6, 5);
    cout << "after path_add(5,6,5):\n";
    cout << "  val[5]: " << hld.point_query(5) << "\n";  // 15
    cout << "  val[2]: " << hld.point_query(2) << "\n";  // 15
    cout << "  val[6]: " << hld.point_query(6) << "\n";  // 5
    cout << "  val[1]: " << hld.point_query(1) << "\n";  // 10 (unchanged)

    return 0;
}
