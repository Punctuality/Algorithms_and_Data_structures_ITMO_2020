//
// Created by Sergey Fedorov on 08/02/2020.
//

#include "../common_utils_string.c"

int partial_sum(int i, int j, const int *numbers){
    int sum = 0;
    for(int index = i; index <= j; index++) {
        sum += numbers[index];
    }
    return sum;
}

// TODO Primitive O(n^3) solution`
int main(){
    // 0 <= N <= 60000 => max 5 sym
    int n = str_to_int(get_line(5));

    int ps[n];
    for (int i = 0; i < n; ++i) {
        // -30000 <= p_i <= +30000 => 6 sym
        ps[i] = str_to_int(get_line(6));
    }

    int max_gravitational_intensivity = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int cur_sum = partial_sum(i, j, ps);
            if (cur_sum >= max_gravitational_intensivity) max_gravitational_intensivity = cur_sum;
        }
    }

    printf("%i", max_gravitational_intensivity);
}