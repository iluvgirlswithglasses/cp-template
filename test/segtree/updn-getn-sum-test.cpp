#include <bits/stdc++.h>
using namespace std;

#include "../../src/segtree/updn-getn-sum.cpp"

int main() {
    // build from array: [1, 2, 3, 4, 5]
    int a[] = {1, 2, 3, 4, 5};
    int n = 5;

    SumSegtree<long long> st(n);
    for (int i = 0; i < n; i++) st.init_set(i, a[i]);
    st.init_build();

    // range sum queries [l, r)
    cout << "sum [0,5): " << st.query(0, 5) << "\n";  // 15
    cout << "sum [0,3): " << st.query(0, 3) << "\n";  // 6
    cout << "sum [2,5): " << st.query(2, 5) << "\n";  // 12

    // range increment: [1,4) += 10 --> [1, 12, 13, 14, 5]
    st.inc(1, 4, 10);
    cout << "after [1,4)+=10, sum [0,5): " << st.query(0, 5) << "\n";  // 45
    cout << "after [1,4)+=10, sum [1,4): " << st.query(1, 4) << "\n";  // 39

    // range increment: [0,5) += 1 --> [2, 13, 14, 15, 6]
    st.inc(0, 5, 1);
    cout << "after [0,5)+=1, sum [0,5): " << st.query(0, 5) << "\n";  // 50

    // range increment: [2,3) -= 5 --> [2, 13, 9, 15, 6]
    st.inc(2, 3, -5);
    cout << "after [2,3)-=5, sum [0,5): " << st.query(0, 5) << "\n";  // 45
    cout << "after [2,3)-=5, sum [2,3): " << st.query(2, 3) << "\n";  // 9

    return 0;
}
