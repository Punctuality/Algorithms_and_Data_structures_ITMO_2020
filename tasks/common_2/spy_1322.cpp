//
// Created by Sergey Fedorov on 14/03/2020.
//
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace::std;

bool letter_comprar(pair<char, int> a, pair<char, int> b){
    if (a.first == b.first){
        return a.second < b.second;
    } else {
        return a.first < b.first;
    }
}

int main() {

    int k;
    cin >> k;

    string encoded;
    cin >> encoded;

    int n = encoded.length();
    pair<char, int> letter_2_position[n];

    for (int i = 0; i < n; ++i) {
        letter_2_position[i] = (pair<char, int>) {encoded[i], i};
    }

    sort(letter_2_position, letter_2_position + n, letter_comprar);

    int back_i = k - 1;
    for (int i = 0; i < n; ++i) {
        pair<char, int> next_letter = letter_2_position[back_i];
        cout << next_letter.first;
        back_i = next_letter.second;
    }
    cout << endl;
}