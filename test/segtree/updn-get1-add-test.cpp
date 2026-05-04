#include <bits/stdc++.h>
using namespace std;

#include "../../src/segtree/updn-get1-add.cpp"

int main() {
    // start with array: [0, 0, 0, 0, 0]
    int n = 5;
    AddSegtree<int> st(n);

    // range add: [0,3) += 2 --> [2, 2, 2, 0, 0]
    st.add(0, 3, 2);
    cout << "after [0,3)+=2: ";
    for (int i = 0; i < n; i++) cout << st.query(i) << " ";
    cout << "\n";  // 2 2 2 0 0

    // range add: [2,5) += 3 --> [2, 2, 5, 3, 3]
    st.add(2, 5, 3);
    cout << "after [2,5)+=3: ";
    for (int i = 0; i < n; i++) cout << st.query(i) << " ";
    cout << "\n";  // 2 2 5 3 3

    // range add: [1,4) += 1 --> [2, 3, 6, 4, 3]
    st.add(1, 4, 1);
    cout << "after [1,4)+=1: ";
    for (int i = 0; i < n; i++) cout << st.query(i) << " ";
    cout << "\n";  // 2 3 6 4 3

    // with initial values
    AddSegtree<int> st2(n);
    for (int i = 0; i < n; i++) st2.init_set(i, i + 1);  // [1, 2, 3, 4, 5]
    st2.init_build();
    st2.add(0, 3, 10);  // [11, 12, 13, 4, 5]
    cout << "with init [1..5], after [0,3)+=10: ";
    for (int i = 0; i < n; i++) cout << st2.query(i) << " ";
    cout << "\n";  // 11 12 13 4 5

    return 0;
}
