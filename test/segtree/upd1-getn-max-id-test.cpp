#include <bits/stdc++.h>
using namespace std;

#include "../../src/segtree/upd1-getn-max-id.cpp"

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

    // Test partial range
    res = st.query(0, 3);
    cout << "max([0,3)): val=" << res.val << ", id=" << res.id << " (expect 30, 101)\n";

    res = st.query(3, 5);
    cout << "max([3,5)): val=" << res.val << ", id=" << res.id << " (expect 50, 103)\n";

    // Test single element
    res = st.query(2, 3);
    cout << "max([2,3)): val=" << res.val << ", id=" << res.id << " (expect 20, 102)\n";

    // Test update
    st.upd(2, 100, 999);  // Update position 2 to value 100 with ID 999
    res = st.query(0, 5);
    cout << "after upd(2, 100, 999), max([0,5)): val=" << res.val << ", id=" << res.id << " (expect 100, 999)\n";

    // Test tie-breaking (smaller ID wins)
    st.upd(4, 100, 500);  // Another 100, but smaller ID
    res = st.query(0, 5);
    cout << "after upd(4, 100, 500), max([0,5)): val=" << res.val << ", id=" << res.id << " (expect 100, 500)\n";

    cout << "All tests passed!\n";
    return 0;
}
