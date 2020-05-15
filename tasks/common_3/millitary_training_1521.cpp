//
// Created by Sergey Fedorov on 07/05/2020.
//

#include <vector>
#include <iostream>

using namespace std;

class BinaryIndexedTree{
private:
    int max_n;
    int *tree;

public:
    BinaryIndexedTree(){
        max_n = 1 << 17;
        tree = (int*) calloc(max_n * 4, sizeof(int));
    }

    void inline sum_update(int x, int amount) {
        for (x += max_n; x > 0; x /= 2)
            tree[x] += amount; // Øynene mine blør på grunn av den koden
    }

    int inline find_k_th_soldier(int start_pos, int k_th) {
        while (start_pos < max_n){
            start_pos *= 2;
            if (k_th > tree[start_pos]) {
                k_th -= tree[start_pos];
                start_pos++;
            }
        }
        return start_pos - max_n;
    }
};

int main() {
    int n, k;
    std::cin >> n >> k;

    BinaryIndexedTree tree = BinaryIndexedTree();

    // Fill tree with soldiers
    // Ugh, bruh.
    for (int i = 0; i < n; ++i) {
        tree.sum_update(i, 1);
    }

    int curr_pos = k - 1;
    for (int i = 0; i < n; ++i) {
        // Find position of next soldier
        int pos = tree.find_k_th_soldier(1, curr_pos + 1);
        cout << pos + 1 << " ";

        // Reduce distance sum
        tree.sum_update(pos, -1);

        int remaining = n - i - 1;
        int next_pos = curr_pos - 1 + k;
        if (i < n - 1) curr_pos = next_pos % remaining;
    }
}