#include <bits/stdc++.h>
using namespace std;

#include "../../src/string/manacher.cpp"

int main() {
    Manacher m;

    // "abacaba" - palindromes centered at each position
    m.build("abacaba");
    cout << "s = \"abacaba\"\n";
    cout << "d_odd:  ";
    for (int i = 0; i < m.n; i++) cout << m.d_odd[i] << " ";
    cout << "\n";  // 0 1 0 3 0 1 0

    cout << "d_even: ";
    for (int i = 0; i < m.n - 1; i++) cout << m.d_even[i] << " ";
    cout << "\n";

    // palindrome lengths
    cout << "Palindrome lengths (odd): ";
    for (int i = 0; i < m.n; i++) cout << 2 * m.d_odd[i] + 1 << " ";
    cout << "\n";   // 0 0 0 0 0 0

    // test is_palindrome
    cout << "is_palindrome(0,6): " << m.is_palindrome(0, 6) << "\n";  // 1 (abacaba)
    cout << "is_palindrome(0,2): " << m.is_palindrome(0, 2) << "\n";  // 1 (aba)
    cout << "is_palindrome(2,4): " << m.is_palindrome(2, 4) << "\n";  // 1 (aca)
    cout << "is_palindrome(0,1): " << m.is_palindrome(0, 1) << "\n";  // 0 (ab)

    // "abaaba" - has even palindrome
    m.build("abaaba");
    cout << "\ns = \"abaaba\"\n";
    cout << "d_odd:  ";
    for (int i = 0; i < m.n; i++) cout << m.d_odd[i] << " ";
    cout << "\n";
    cout << "d_even: ";
    for (int i = 0; i < m.n - 1; i++) cout << m.d_even[i] << " ";
    cout << "\n";
    cout << "is_palindrome(0,5): " << m.is_palindrome(0, 5) << "\n";  // 1 (abaaba)
    cout << "is_palindrome(0,2): " << m.is_palindrome(0, 2) << "\n";  // 1 (aba)

    return 0;
}
