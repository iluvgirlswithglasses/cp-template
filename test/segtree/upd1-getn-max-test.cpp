#include <bits/stdc++.h>
using namespace std;

#include "../../src/segtree/upd1-getn-max.cpp"

int main() {
    // build from array: [3, 1, 4, 1, 5, 9, 2, 6]
    int a[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = 8;

    MaxSegtree<int> st(n);
    for (int i = 0; i < n; i++) st.init_set(i, a[i]);
    st.init_build();

    // range max queries [l, r)
    cout << "max [0,8): " << st.query(0, 8) << "\n";  // 9
    cout << "max [0,4): " << st.query(0, 4) << "\n";  // 4
    cout << "max [4,8): " << st.query(4, 8) << "\n";  // 9
    cout << "max [2,5): " << st.query(2, 5) << "\n";  // 5

    // point update: a[5] = 0
    st.upd(5, 0);
    cout << "after a[5]=0, max [0,8): " << st.query(0, 8) << "\n";  // 6

    // point update: a[7] = 10
    st.upd(7, 10);
    cout << "after a[7]=10, max [0,8): " << st.query(0, 8) << "\n";  // 10

    return 0;
}
