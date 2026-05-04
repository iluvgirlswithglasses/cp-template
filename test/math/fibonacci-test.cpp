#include <bits/stdc++.h>
using namespace std;

#include "../../src/math/fibonacci.cpp"

int main() {
    // first few fibonacci numbers: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    cout << "F(0): " << fib(0).first << "\n";   // 0
    cout << "F(1): " << fib(1).first << "\n";   // 1
    cout << "F(2): " << fib(2).first << "\n";   // 1
    cout << "F(5): " << fib(5).first << "\n";   // 5
    cout << "F(10): " << fib(10).first << "\n"; // 55
    cout << "F(20): " << fib(20).first << "\n"; // 6765

    // with modulo for large n
    int64_t mod = 1e9 + 7;
    cout << "F(50) mod 1e9+7: " << fib(50, mod).first << "\n";  // 12586269025 % mod = 586268941
    cout << "F(100) mod 1e9+7: " << fib(100, mod).first << "\n";
    cout << "F(1000000) mod 1e9+7: " << fib(1000000, mod).first << "\n";

    return 0;
}
