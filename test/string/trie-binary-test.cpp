#include <bits/stdc++.h>
using namespace std;

#include "../../src/string/trie-binary.cpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    Trie tr;

    // Test basic insert and k-th largest
    tr.add(5);   // binary: 00...0101
    tr.add(10);  // binary: 00...1010
    tr.add(3);   // binary: 00...0011
    tr.add(7);   // binary: 00...0111

    cout << "Size after adding 5, 10, 3, 7: " << tr.size() << "\n";
    // Sorted desc: 10, 7, 5, 3
    cout << "0th largest (10): " << tr.kth(0) << "\n";
    cout << "1st largest (7): " << tr.kth(1) << "\n";
    cout << "2nd largest (5): " << tr.kth(2) << "\n";
    cout << "3rd largest (3): " << tr.kth(3) << "\n";

    // Test remove
    tr.rem(10);
    cout << "After removing 10, size: " << tr.size() << "\n";
    cout << "0th largest (7): " << tr.kth(0) << "\n";

    // Test with duplicates
    tr.add(5);
    tr.add(5);
    cout << "After adding 5 twice, size: " << tr.size() << "\n";
    // Sorted desc: 7, 5, 5, 5, 3
    cout << "0th largest (7): " << tr.kth(0) << "\n";
    cout << "1st largest (5): " << tr.kth(1) << "\n";
    cout << "2nd largest (5): " << tr.kth(2) << "\n";
    cout << "3rd largest (5): " << tr.kth(3) << "\n";
    cout << "4th largest (3): " << tr.kth(4) << "\n";

    // Test with larger numbers
    Trie tr2;
    tr2.add(1000000);
    tr2.add(2000000);
    tr2.add(500000);
    cout << "Large nums - 0th largest (2000000): " << tr2.kth(0) << "\n";
    cout << "Large nums - 2nd largest (500000): " << tr2.kth(2) << "\n";

    cout << "All tests passed!\n";
    return 0;
}
