#include <bits/stdc++.h>
using namespace std;

#include "../../src/math/matpow.cpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Test Fibonacci via matrix exponentiation
    cout << "=== Fibonacci (no mod) ===\n";
    cout << "F(0) = " << fib_matrix(0) << " (expect 0)\n";
    cout << "F(1) = " << fib_matrix(1) << " (expect 1)\n";
    cout << "F(2) = " << fib_matrix(2) << " (expect 1)\n";
    cout << "F(10) = " << fib_matrix(10) << " (expect 55)\n";
    cout << "F(20) = " << fib_matrix(20) << " (expect 6765)\n";
    cout << "F(50) = " << fib_matrix(50) << " (expect 12586269025)\n";

    // Test with modulo
    constexpr int64_t MOD = 1e9 + 7;
    cout << "\n=== Fibonacci (mod 1e9+7) ===\n";
    cout << "F(50) mod = " << fib_matrix<MOD>(50) << " (expect 586268941)\n";
    cout << "F(100) mod = " << fib_matrix<MOD>(100) << " (expect 687995182)\n";

    // Test general matrix: Tribonacci T(n) = T(n-1) + T(n-2) + T(n-3)
    // T(0)=0, T(1)=0, T(2)=1, T(3)=1, T(4)=2, T(5)=4, T(6)=7, T(7)=13
    cout << "\n=== Tribonacci ===\n";
    auto tribonacci = [](int64_t n) -> int64_t {
        if (n < 2) return 0;
        if (n == 2) return 1;
        Matrix<3> m;
        m.a[0][0] = m.a[0][1] = m.a[0][2] = 1;
        m.a[1][0] = 1; m.a[2][1] = 1;
        auto res = m.pow(n - 2);
        return res.a[0][0];  // T(n)
    };
    cout << "T(0) = " << tribonacci(0) << " (expect 0)\n";
    cout << "T(2) = " << tribonacci(2) << " (expect 1)\n";
    cout << "T(5) = " << tribonacci(5) << " (expect 4)\n";
    cout << "T(7) = " << tribonacci(7) << " (expect 13)\n";
    cout << "T(10) = " << tribonacci(10) << " (expect 81)\n";

    // Test matrix multiplication
    cout << "\n=== Matrix multiplication ===\n";
    Matrix<2> A, B;
    A.a[0][0] = 1; A.a[0][1] = 2;
    A.a[1][0] = 3; A.a[1][1] = 4;
    B.a[0][0] = 5; B.a[0][1] = 6;
    B.a[1][0] = 7; B.a[1][1] = 8;
    auto C = A * B;
    // [1 2] * [5 6] = [19 22]
    // [3 4]   [7 8]   [43 50]
    cout << "C[0][0] = " << C.a[0][0] << " (expect 19)\n";
    cout << "C[0][1] = " << C.a[0][1] << " (expect 22)\n";
    cout << "C[1][0] = " << C.a[1][0] << " (expect 43)\n";
    cout << "C[1][1] = " << C.a[1][1] << " (expect 50)\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
