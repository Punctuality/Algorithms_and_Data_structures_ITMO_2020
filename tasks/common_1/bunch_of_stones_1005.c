//
// Created by Sergey Fedorov on 07/02/2020.
//

#include "../common_utils_string.c"

// O(2^(n+1)). // Tried to minimize by cutting off with comparison with half-sum.
int place_stones(const int *stones, int i, int n, int bunch_1, int bunch_2, int sum){
    int cur_stone = stones[i];
    if (bunch_1 >= sum / 2) {
        return abs(bunch_1*2 - sum);
    } else if (bunch_2 >= sum / 2) {
        return abs(bunch_2*2 - sum);
    } else if (i < n) {
        int var_1 = place_stones(stones, i + 1, n, bunch_1 + cur_stone, bunch_2, sum);
        int var_2 = place_stones(stones, i + 1, n, bunch_1, bunch_2 + cur_stone, sum);
        return var_1 < var_2 ? var_1 : var_2;
    } else {
        return abs(bunch_1 - bunch_2);
    }
}

int main() {
    // 1 <= N <= 20 => max 2 sym
    int n = str_to_int(get_line(2));

    // 1 <= Wi <= 100 000 => ~ 5 sym
    char **raw_stones = str_split(get_line(5), ' ');

    int stones[n];
    int weight_sum = 0;
    for (int i = 0; i < n; i++) {
        stones[i] = str_to_int(raw_stones[i]);
        weight_sum += stones[i];
    }
    // qsort_ints(stones, n); Presumably on big N. Sorting will be useful.

    int minimal_diff = place_stones(stones, 0, n, 0, 0, weight_sum);

    printf("%i\n", minimal_diff);
}