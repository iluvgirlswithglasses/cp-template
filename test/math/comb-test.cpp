#include <bits/stdc++.h>
using namespace std;

#include "../../src/math/comb.cpp"

int main() {
    // basic comb without modulo
    cout << "comb(5,2): " << comb(5, 2) << "\n";   // 10
    cout << "comb(10,3): " << comb(10, 3) << "\n"; // 120
    cout << "comb(10,0): " << comb(10, 0) << "\n"; // 1
    cout << "comb(10,10): " << comb(10, 10) << "\n"; // 1
    cout << "comb(20,10): " << comb(20, 10) << "\n"; // 184756
    cout << "comb(5,7): " << comb(5, 7) << "\n";   // 0 (k > n)

    // precomputed with modulo
    constexpr int64_t MOD = 1e9 + 7;
    Comb<100001, MOD> c;

    cout << "\nWith MOD = 1e9+7:\n";
    cout << "comb(5,2): " << c.comb(5, 2) << "\n";     // 10
    cout << "comb(10,3): " << c.comb(10, 3) << "\n";   // 120
    cout << "comb(100,50): " << c.comb(100, 50) << "\n"; // 538992043
    cout << "comb(100000,50000): " << c.comb(100000, 50000) << "\n";

    // permutations
    cout << "\nPermutations:\n";
    cout << "perm(5,2): " << c.perm(5, 2) << "\n";   // 20
    cout << "perm(10,3): " << c.perm(10, 3) << "\n"; // 720

    return 0;
}
