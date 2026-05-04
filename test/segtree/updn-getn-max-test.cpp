#include <bits/stdc++.h>
using namespace std;

#include "../../src/segtree/updn-getn-max.cpp"

int main() {
    // build from array: [5, 3, 7, 1, 4]
    int a[] = {5, 3, 7, 1, 4};
    int n = 5;

    MaxSegtree<int> st(n);
    for (int i = 0; i < n; i++) st.init_set(i, a[i]);
    st.init_build();

    // range max queries [l, r)
    cout << "max [0,5): " << st.query(0, 5) << "\n";  // 7
    cout << "max [0,3): " << st.query(0, 3) << "\n";  // 7
    cout << "max [3,5): " << st.query(3, 5) << "\n";  // 4

    // range increment: [0,3) += 5 --> [10, 8, 12, 1, 4]
    st.inc(0, 3, 5);
    cout << "after [0,3)+=5, max [0,5): " << st.query(0, 5) << "\n";  // 12
    cout << "after [0,3)+=5, max [3,5): " << st.query(3, 5) << "\n";  // 4

    // range increment: [2,5) += 10 --> [10, 8, 22, 11, 14]
    st.inc(2, 5, 10);
    cout << "after [2,5)+=10, max [0,5): " << st.query(0, 5) << "\n";  // 22
    cout << "after [2,5)+=10, max [0,2): " << st.query(0, 2) << "\n";  // 10

    return 0;
}
