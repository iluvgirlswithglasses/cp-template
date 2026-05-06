#include <bits/stdc++.h>
using namespace std;

#include "../../src/segtree/updn-getn-max-id.cpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    MaxSegtree<int64_t> st(5);

    // Initialize: values [10, 30, 20, 50, 40] with IDs [100, 101, 102, 103, 104]
    st.init_set(0, 10, 100);
    st.init_set(1, 30, 101);
    st.init_set(2, 20, 102);
    st.init_set(3, 50, 103);
    st.init_set(4, 40, 104);
    st.init_build();

    // Test full range query
    auto res = st.query(0, 5);
    cout << "max([0,5)): val=" << res.val << ", id=" << res.id << " (expect 50, 103)\n";

    // Test range increment
    st.inc(1, 4, 30);  // Add 30 to positions 1, 2, 3: [10, 60, 50, 80, 40]
    res = st.query(0, 5);
    cout << "after inc([1,4), 30), max([0,5)): val=" << res.val << ", id=" << res.id << " (expect 80, 103)\n";

    // Test partial range after increment
    res = st.query(0, 3);
    cout << "max([0,3)): val=" << res.val << ", id=" << res.id << " (expect 60, 101)\n";

    // Another increment
    st.inc(0, 2, 50);  // Add 50 to positions 0, 1: [60, 110, 50, 80, 40]
    res = st.query(0, 5);
    cout << "after inc([0,2), 50), max([0,5)): val=" << res.val << ", id=" << res.id << " (expect 110, 101)\n";

    // Test that ID is preserved after increments
    res = st.query(3, 4);
    cout << "max([3,4)): val=" << res.val << ", id=" << res.id << " (expect 80, 103)\n";

    cout << "All tests passed!\n";
    return 0;
}
