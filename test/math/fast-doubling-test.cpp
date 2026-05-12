#include <bits/stdc++.h>
using namespace std;

#include "../../src/math/fast-doubling.cpp"

const int64_t MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Test Fibonacci
    cout << "=== Fibonacci (no mod) ===\n";
    cout << "F(0) = " << FibDoubling<>::get(0) << " (expect 0)\n";
    cout << "F(1) = " << FibDoubling<>::get(1) << " (expect 1)\n";
    cout << "F(10) = " << FibDoubling<>::get(10) << " (expect 55)\n";
    cout << "F(50) = " << FibDoubling<>::get(50) << " (expect 12586269025)\n";

    cout << "\n=== Fibonacci (mod 1e9+7) ===\n";
    cout << "F(100) mod = " << FibDoubling<MOD>::get(100) << " (expect 687995182)\n";
    cout << "F(1e18) mod = " << FibDoubling<MOD>::get(1000000000000000000LL) << "\n";

    // Test custom recurrence: a(2k) = 2*a(k), a(2k+1) = a(k) - 3*a(k+1)
    // Base cases: a(0)=0, a(1)=1, a(2)=2
    cout << "\n=== Custom recurrence (a(2k)=2*a(k), a(2k+1)=a(k)-3*a(k+1)) ===\n";

    // Reference values from DP
    // a(3) = a(1) - 3*a(2) = 1 - 6 = -5
    // a(4) = 2*a(2) = 4
    // a(5) = a(2) - 3*a(3) = 2 - (-15) = 17
    cout << "a(0) = " << FastDoubling<MOD>::get(0, 0, 1, 2) << " (expect 0)\n";
    cout << "a(1) = " << FastDoubling<MOD>::get(1, 0, 1, 2) << " (expect 1)\n";
    cout << "a(2) = " << FastDoubling<MOD>::get(2, 0, 1, 2) << " (expect 2)\n";
    cout << "a(3) = " << FastDoubling<MOD>::get(3, 0, 1, 2) << " (expect 1000000002 = -5 mod)\n";
    cout << "a(4) = " << FastDoubling<MOD>::get(4, 0, 1, 2) << " (expect 4)\n";
    cout << "a(5) = " << FastDoubling<MOD>::get(5, 0, 1, 2) << " (expect 17)\n";
    cout << "a(1000000) = " << FastDoubling<MOD>::get(1000000, 0, 1, 2) << " (expect 82076480)\n";

    // Test large n
    cout << "\n=== Large n ===\n";
    cout << "a(1e18) mod = " << FastDoubling<MOD>::get(1000000000000000000LL, 0, 1, 2) << "\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
