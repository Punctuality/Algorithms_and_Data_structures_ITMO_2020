//
// Created by Sergey Fedorov on 08/02/2020.
//

#include "../../utils/common_utils_string.c"

int max(int a, int b){
    return (a > b) ? a : b;
}

int GLOBAL_MAX = 0;

int intensity_max(int* values, int n){
    int right_side = values[n];
    int left_side = 0;
    if (n > 0){
        left_side = intensity_max(values, n - 1);
    }
    left_side += right_side;
    int cur_result = max(left_side, right_side);
    GLOBAL_MAX = max(GLOBAL_MAX, cur_result);
    return cur_result;
}

int main(){
    // 0 <= N <= 60000 => max 5 sym
    int n = str_to_int(get_line(5));

    int ps[n];
    for (int i = 0; i < n; ++i) ps[i] = str_to_int(get_line(6));

    intensity_max(ps, n-1);

    printf("%i", GLOBAL_MAX);
}