//
// Created by Sergey Fedorov on 13/03/2020.
//

#include <iostream>
#include <algorithm>

using namespace::std;

typedef struct {
    int number, quantity;
} sign;

bool sign_compar(sign a, sign b){
    return a.quantity > b.quantity;
}

void bubble_sort_step(sign* signs, int length, pair<int, int> index_pair){
    if (index_pair.second < length) {
        while(signs[index_pair.first].quantity < signs[index_pair.second].quantity) {
            sign first = signs[index_pair.first];
            sign second = signs[index_pair.second];
            signs[index_pair.second] = first;
            signs[index_pair.first] = second;
            index_pair.first++; index_pair.second++;
            if (index_pair.second == length) break;
        }
    }
}

int main(){
    int k;
    cin >> k;

    int n = 0;
    sign signs[k];

    for (int i = 0; i < k; i++) {
        int quantity;
        cin >> quantity;
        n += quantity;
        signs[i] = (sign) {i + 1, quantity};
    }

    sort(signs, signs + k, sign_compar);

    while (n--) {
        std::cout << signs[0].number << " ";
        signs[0].quantity--;
        if (k > 1 && signs[1].quantity != 0) {
            std::cout << signs[1].number << " ";
            signs[1].quantity--;
        }

        // Two iterations of bubble sort will be enough to rise max element by 2 positions.
        bubble_sort_step(signs, k, {1, 2});
        bubble_sort_step(signs, k, {0, 1});

        if (signs[0].quantity <= 0) break;
    }
    std::cout << endl;
}