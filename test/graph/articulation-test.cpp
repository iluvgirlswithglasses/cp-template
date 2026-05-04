#include <bits/stdc++.h>
using namespace std;

#include "../../src/graph/articulation.cpp"

int main() {
    /*
        Undirected graph (0-indexed):
        0 -- 1 -- 2
             |    |
             3 -- 4 -- 5

        Articulation points: 1, 4
    */
    ArticulationPoints<10> ap;
    ap.n = 6;
    ap.add_edge(0, 1);
    ap.add_edge(1, 2);
    ap.add_edge(1, 3);
    ap.add_edge(2, 4);
    ap.add_edge(3, 4);
    ap.add_edge(4, 5);

    auto& cuts = ap.build();
    cout << "Number of articulation points: " << cuts.size() << "\n";
    sort(cuts.begin(), cuts.end());
    cout << "Articulation points: ";
    for (int u : cuts) cout << u << " ";
    cout << "\n";  // 1 4

    cout << "is_cut[0]: " << ap.is_cut[0] << "\n";  // 0
    cout << "is_cut[1]: " << ap.is_cut[1] << "\n";  // 1
    cout << "is_cut[4]: " << ap.is_cut[4] << "\n";  // 1
    cout << "is_cut[5]: " << ap.is_cut[5] << "\n";  // 0

    return 0;
}
