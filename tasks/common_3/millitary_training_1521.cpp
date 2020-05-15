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
        tree = (int*) calloc(2 << 18, sizeof(int));
    }

    void inline sum_update(int x, int amount) {
        for (x += max_n; x > 0; x /= 2)
            tree[x] += amount; // Øynene mine blør på grunn av den koden
    }

    int inline find_k_th(int start_pos, int k_th) {
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

    for (int i = 0; i < n; ++i) {
        tree.sum_update(i, 1);
    }

    int currPos = k - 1;
    for (int i = 0; i < n; ++i) {
        int pos = tree.find_k_th(1, currPos + 1);
        tree.sum_update(pos, -1);
        std::cout << pos + 1 << " ";
        if (i < n - 1) currPos = (currPos - 1 + k) % (n - i - 1);
    }
    return 0;
}