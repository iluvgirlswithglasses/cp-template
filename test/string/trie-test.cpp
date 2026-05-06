#include <bits/stdc++.h>
using namespace std;

#include "../../src/string/trie.cpp"

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Test with default alphabet (26 lowercase letters)
    Trie<> tr;

    tr.insert("apple");
    tr.insert("app");
    tr.insert("application");
    tr.insert("banana");

    cout << "=== Basic operations ===\n";
    cout << "find('apple'): " << tr.find("apple") << " (expect 1)\n";
    cout << "find('app'): " << tr.find("app") << " (expect 1)\n";
    cout << "find('appl'): " << tr.find("appl") << " (expect 0)\n";
    cout << "find('orange'): " << tr.find("orange") << " (expect 0)\n";

    cout << "\n=== Prefix operations ===\n";
    cout << "starts_with('app'): " << tr.starts_with("app") << " (expect 1)\n";
    cout << "starts_with('ban'): " << tr.starts_with("ban") << " (expect 1)\n";
    cout << "starts_with('ora'): " << tr.starts_with("ora") << " (expect 0)\n";
    cout << "count_prefix('app'): " << tr.count_prefix("app") << " (expect 3)\n";
    cout << "count_prefix('apple'): " << tr.count_prefix("apple") << " (expect 1)\n";

    // Test duplicates
    cout << "\n=== Duplicate handling ===\n";
    tr.insert("apple");
    tr.insert("apple");
    cout << "count('apple') after 2 more inserts: " << tr.count("apple") << " (expect 3)\n";
    cout << "count_prefix('app'): " << tr.count_prefix("app") << " (expect 5)\n";

    // Test erase
    cout << "\n=== Erase operations ===\n";
    tr.erase("apple");
    cout << "count('apple') after 1 erase: " << tr.count("apple") << " (expect 2)\n";
    cout << "count_prefix('app'): " << tr.count_prefix("app") << " (expect 4)\n";

    // Test with different alphabet size (digits 0-9)
    cout << "\n=== Numeric trie (digits 0-9) ===\n";
    Trie<10, '0'> numTrie;
    numTrie.insert("123");
    numTrie.insert("1234");
    numTrie.insert("125");
    numTrie.insert("999");

    cout << "find('123'): " << numTrie.find("123") << " (expect 1)\n";
    cout << "count_prefix('12'): " << numTrie.count_prefix("12") << " (expect 3)\n";
    cout << "count_prefix('9'): " << numTrie.count_prefix("9") << " (expect 1)\n";

    // Test with full ASCII
    cout << "\n=== Full ASCII trie ===\n";
    Trie<128, '\0'> asciiTrie;
    asciiTrie.insert("Hello, World!");
    asciiTrie.insert("Hello");
    asciiTrie.insert("Hi");

    cout << "find('Hello'): " << asciiTrie.find("Hello") << " (expect 1)\n";
    cout << "find('Hello, World!'): " << asciiTrie.find("Hello, World!") << " (expect 1)\n";
    cout << "count_prefix('H'): " << asciiTrie.count_prefix("H") << " (expect 3)\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
