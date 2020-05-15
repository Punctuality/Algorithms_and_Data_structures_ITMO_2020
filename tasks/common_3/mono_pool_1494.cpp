//
// Created by Sergey Fedorov on 07/05/2020.
//
#include <iostream>
#include <stack>

using namespace::std;

int main() {
    int n;
    cin >> n;
    stack<int> balls;
    int max_ball = -1;

    for (int i = 0; i < n; i++) {
        int current;
        cin >> current;

        if (current > max_ball) {
            for (int j = max_ball + 1; j < current; j++) {
                balls.push(j); // Так как ревизор достал все шары, то имеем заполнить стек one-by-one
            }
            max_ball = current;
        } else {
            if (current == balls.top()) {
                balls.pop();
            } else { // Так как в начале был максимальный шар, то затем должны быть только шары меньше и в установленном порядке
                cout << "Cheater" << endl;
                return 0;
            }
        }
    }

    cout << "Not a proof" << endl;
    return 0;
}