#include <bits/stdc++.h>
using namespace std;

#include "../../src/tree/hld-upd1-getn-max.cpp"

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

    // set node values: node i has value i*10
    for (int i = 1; i <= 7; i++) hld.update(i, i * 10);

    // path max queries
    cout << "max(5,6): " << hld.path_query(5, 6) << "\n";  // max(50,20,60) = 60
    cout << "max(5,7): " << hld.path_query(5, 7) << "\n";  // max(50,20,10,40,70) = 70
    cout << "max(3,3): " << hld.path_query(3, 3) << "\n";  // 30
    cout << "max(1,7): " << hld.path_query(1, 7) << "\n";  // max(10,40,70) = 70

    // update node 2 to 100
    hld.update(2, 100);
    cout << "after update(2,100):\n";
    cout << "  max(5,6): " << hld.path_query(5, 6) << "\n";  // max(50,100,60) = 100
    cout << "  max(5,7): " << hld.path_query(5, 7) << "\n";  // max(50,100,10,40,70) = 100

    // update node 1 to 200
    hld.update(1, 200);
    cout << "after update(1,200):\n";
    cout << "  max(5,7): " << hld.path_query(5, 7) << "\n";  // max(50,100,200,40,70) = 200
    cout << "  max(3,7): " << hld.path_query(3, 7) << "\n";  // max(30,200,40,70) = 200

    return 0;
}
