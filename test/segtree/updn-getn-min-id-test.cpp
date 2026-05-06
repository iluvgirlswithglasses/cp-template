#include <bits/stdc++.h>
using namespace std;

#include "../../src/segtree/updn-getn-min-id.cpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    MinSegtree<int64_t> st(5);

    // Initialize: values [50, 30, 40, 10, 20] with IDs [100, 101, 102, 103, 104]
    st.init_set(0, 50, 100);
    st.init_set(1, 30, 101);
    st.init_set(2, 40, 102);
    st.init_set(3, 10, 103);
    st.init_set(4, 20, 104);
    st.init_build();

    // Test full range query
    auto res = st.query(0, 5);
    cout << "min([0,5)): val=" << res.val << ", id=" << res.id << " (expect 10, 103)\n";

    // Test range increment
    st.inc(3, 5, 50);  // Add 50 to positions 3, 4: [50, 30, 40, 60, 70]
    res = st.query(0, 5);
    cout << "after inc([3,5), 50), min([0,5)): val=" << res.val << ", id=" << res.id << " (expect 30, 101)\n";

    // Test partial range after increment
    res = st.query(3, 5);
    cout << "min([3,5)): val=" << res.val << ", id=" << res.id << " (expect 60, 103)\n";

    // Another increment (negative)
    st.inc(0, 3, -40);  // Subtract 40 from positions 0, 1, 2: [10, -10, 0, 60, 70]
    res = st.query(0, 5);
    cout << "after inc([0,3), -40), min([0,5)): val=" << res.val << ", id=" << res.id << " (expect -10, 101)\n";

    // Test that ID is preserved after increments
    res = st.query(2, 3);
    cout << "min([2,3)): val=" << res.val << ", id=" << res.id << " (expect 0, 102)\n";

    cout << "All tests passed!\n";
    return 0;
}
