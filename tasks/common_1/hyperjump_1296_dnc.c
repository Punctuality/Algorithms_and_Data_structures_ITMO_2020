//
// Created by Sergey Fedorov on 08/02/2020.
//

#include "../../utils/common_utils_string.c"

int max(int a, int b){
    return (a > b) ? a : b;
}

int divide_n_conquer(int* values, int a, int b){
    if (a != b) {
        int left_side = divide_n_conquer(values, a, a + (b-a) / 2);
        int right_side = divide_n_conquer(values, a + (b-a) / 2 + 1, b);

        // Computing mid crossing sum
        int m = (a + b) / 2;

        int temp_sum = 0;
        int mid_left_sum = 0;
        for (int i = m; i >= a; i--)
        {
            temp_sum = temp_sum + values[i];
            mid_left_sum = max(mid_left_sum, temp_sum);
        }

        temp_sum = 0;
        int mid_right_sum = 0;
        for (int i = m+1; i <= b; i++)
        {
            temp_sum = temp_sum + values[i];
            mid_right_sum = max(mid_right_sum, temp_sum);
        }

        return max(mid_left_sum + mid_right_sum, max(left_side, right_side));
    } else {
        return values[a];
    }
}

int main(){
    // 0 <= N <= 60000 => max 5 sym
    int n = str_to_int(get_line(5));

    int ps[n];

    for (int i = 0; i < n; ++i) ps[i] = str_to_int(get_line(6));

    if (n > 0){
        printf("%i", divide_n_conquer(ps, 0, n-1));
    } else {
        printf("0");
    }
}