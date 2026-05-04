#include <bits/stdc++.h>
using namespace std;

#include "../../src/tree/hld-upd1-getn-sum.cpp"

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

    // set node values: node i has value i
    for (int i = 1; i <= 7; i++) hld.update(i, i);

    // path sum queries
    cout << "sum(5,6): " << hld.path_query(5, 6) << "\n";  // 5+2+6 = 13
    cout << "sum(5,7): " << hld.path_query(5, 7) << "\n";  // 5+2+1+4+7 = 19
    cout << "sum(3,3): " << hld.path_query(3, 3) << "\n";  // 3
    cout << "sum(1,7): " << hld.path_query(1, 7) << "\n";  // 1+4+7 = 12

    // update node 2 to 100
    hld.update(2, 100);
    cout << "after update(2,100):\n";
    cout << "  sum(5,6): " << hld.path_query(5, 6) << "\n";  // 5+100+6 = 111
    cout << "  sum(5,7): " << hld.path_query(5, 7) << "\n";  // 5+100+1+4+7 = 117

    // add 10 to node 1
    hld.add(1, 10);
    cout << "after add(1,10):\n";
    cout << "  sum(5,7): " << hld.path_query(5, 7) << "\n";  // 5+100+11+4+7 = 127

    return 0;
}
