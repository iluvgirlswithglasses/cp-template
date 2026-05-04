#include <bits/stdc++.h>
using namespace std;

#include "../../src/segtree/upd1-getn-min.cpp"

int main() {
    // build from array: [3, 1, 4, 1, 5, 9, 2, 6]
    int a[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = 8;

    MinSegtree<int> st(n);
    for (int i = 0; i < n; i++) st.init_set(i, a[i]);
    st.init_build();

    // range min queries [l, r)
    cout << "min [0,8): " << st.query(0, 8) << "\n";  // 1
    cout << "min [0,4): " << st.query(0, 4) << "\n";  // 1
    cout << "min [4,8): " << st.query(4, 8) << "\n";  // 2
    cout << "min [2,5): " << st.query(2, 5) << "\n";  // 1

    // point update: a[1] = 10
    st.upd(1, 10);
    cout << "after a[1]=10, min [0,4): " << st.query(0, 4) << "\n";  // 1 (a[3])

    // point update: a[3] = 7
    st.upd(3, 7);
    cout << "after a[3]=7, min [0,4): " << st.query(0, 4) << "\n";  // 3 (a[0])

    return 0;
}
