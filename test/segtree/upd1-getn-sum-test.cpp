#include <bits/stdc++.h>
using namespace std;

#include "../../src/segtree/upd1-getn-sum.cpp"

int main() {
    // build from array: [1, 2, 3, 4, 5]
    int a[] = {1, 2, 3, 4, 5};
    int n = 5;

    SumSegtree<int> st(n);
    for (int i = 0; i < n; i++) st.init_set(i, a[i]);
    st.init_build();

    // range sum queries [l, r)
    cout << "sum [0,5): " << st.query(0, 5) << "\n";  // 15
    cout << "sum [0,3): " << st.query(0, 3) << "\n";  // 6
    cout << "sum [2,5): " << st.query(2, 5) << "\n";  // 12
    cout << "sum [1,4): " << st.query(1, 4) << "\n";  // 9

    // point update: a[2] = 10
    st.upd(2, 10);
    cout << "after a[2]=10, sum [0,5): " << st.query(0, 5) << "\n";  // 22

    // add delta: a[0] += 5
    st.add(0, 5);
    cout << "after a[0]+=5, sum [0,5): " << st.query(0, 5) << "\n";  // 27

    return 0;
}
