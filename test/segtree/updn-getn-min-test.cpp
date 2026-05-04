#include <bits/stdc++.h>
using namespace std;

#include "../../src/segtree/updn-getn-min.cpp"

int main() {
    // build from array: [5, 3, 7, 1, 4]
    int a[] = {5, 3, 7, 1, 4};
    int n = 5;

    MinSegtree<int> st(n);
    for (int i = 0; i < n; i++) st.init_set(i, a[i]);
    st.init_build();

    // range min queries [l, r)
    cout << "min [0,5): " << st.query(0, 5) << "\n";  // 1
    cout << "min [0,3): " << st.query(0, 3) << "\n";  // 3
    cout << "min [2,5): " << st.query(2, 5) << "\n";  // 1

    // range increment: [1,4) += 10 --> [5, 13, 17, 11, 4]
    st.inc(1, 4, 10);
    cout << "after [1,4)+=10, min [0,5): " << st.query(0, 5) << "\n";  // 4
    cout << "after [1,4)+=10, min [1,4): " << st.query(1, 4) << "\n";  // 11

    // range increment: [0,2) -= 3 --> [2, 10, 17, 11, 4]
    st.inc(0, 2, -3);
    cout << "after [0,2)-=3, min [0,5): " << st.query(0, 5) << "\n";  // 2
    cout << "after [0,2)-=3, min [0,2): " << st.query(0, 2) << "\n";  // 2

    return 0;
}
