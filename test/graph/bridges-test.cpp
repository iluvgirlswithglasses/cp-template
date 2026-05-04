#include <bits/stdc++.h>
using namespace std;

#include "../../src/graph/bridges.cpp"

int main() {
    /*
        Undirected graph (0-indexed):
        0 -- 1 -- 2
             |    |
             3 -- 4 -- 5

        Bridges: (1,2), (4,5)
        (0-1-3 form a cycle, 2-4 form a cycle with 1-3)
    */
    Bridges<10> br;
    br.n = 6;
    br.add_edge(0, 1);
    br.add_edge(1, 2);
    br.add_edge(1, 3);
    br.add_edge(2, 4);
    br.add_edge(3, 4);
    br.add_edge(4, 5);

    auto& bridges = br.build();
    cout << "Number of bridges: " << bridges.size() << "\n";
    cout << "Bridges:\n";
    for (auto [u, v] : bridges)
        cout << "  " << u << " -- " << v << "\n";

    // simple chain: all edges are bridges
    Bridges<10> br2;
    br2.n = 4;
    br2.add_edge(0, 1);
    br2.add_edge(1, 2);
    br2.add_edge(2, 3);
    auto& bridges2 = br2.build();
    cout << "Chain bridges: " << bridges2.size() << "\n";  // 3

    return 0;
}
