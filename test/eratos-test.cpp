#include <bits/stdc++.h>
using namespace std;

#include "../src/eratos.cpp"

int main() {
    // primality check
    cout << "is_prime(17): " << er.is_prime(17) << "\n";      // 1
    cout << "is_prime(18): " << er.is_prime(18) << "\n";      // 0

    // first 10 primes
    cout << "first 10 primes: ";
    for (int i = 0; i < 10; i++) cout << er.p[i] << " ";
    cout << "\n";  // 2 3 5 7 11 13 17 19 23 29

    // unique prime factors of 360 = 2^3 * 3^2 * 5
    cout << "fact(360): ";
    for (auto f : er.fact(360)) cout << f << " ";
    cout << "\n";  // 2 3 5

    // full factorization
    cout << "fact_map(360): ";
    for (auto [p, e] : er.fact_map(360)) cout << p << "^" << e << " ";
    cout << "\n";  // 2^3 3^2 5^1

    // all divisors of 12
    auto divs = er.get_divisors(12);
    sort(divs.begin(), divs.end());
    cout << "divisors(12): ";
    for (auto d : divs) cout << d << " ";
    cout << "\n";  // 1 2 3 4 6 12

    return 0;
}
