//
// Created by Sergey Fedorov on 08/02/2020.
//

#include "../../utils/common_utils_string.c"

int main(){
    // 0 <= N <= 60000 => max 5 sym
    int n = str_to_int(get_line(5));

    int grav_sum = 0;
    int max_grav = 0;

    for (int i = 0; i < n; ++i) {
        // -30000 <= p_i <= +30000 => 6 sym
        int cur_intensity = str_to_int(get_line(6));
        grav_sum += cur_intensity;

        if (grav_sum < 0){
            grav_sum = 0;
        } else if (grav_sum >= max_grav) {
            max_grav = grav_sum;
        }
    }

    printf("%i", max_grav);
}