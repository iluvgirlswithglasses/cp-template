#include <bits/stdc++.h>
using namespace std;

#include "../../src/math/binpow.cpp"

int main() {
    // basic power
    cout << "2^10: " << binpow(2, 10) << "\n";      // 1024
    cout << "3^5: " << binpow(3, 5) << "\n";        // 243
    cout << "7^0: " << binpow(7, 0) << "\n";        // 1
    cout << "2^20: " << binpow(2, 20) << "\n";      // 1048576

    // power with modulo
    int64_t mod = 1e9 + 7;
    cout << "2^10 mod 1e9+7: " << binpow(2, 10, mod) << "\n";  // 1024
    cout << "2^100 mod 1e9+7: " << binpow(2, 100, mod) << "\n";  // 976371285
    cout << "123456789^987654321 mod 1e9+7: " << binpow(123456789, 987654321, mod) << "\n";

    return 0;
}
