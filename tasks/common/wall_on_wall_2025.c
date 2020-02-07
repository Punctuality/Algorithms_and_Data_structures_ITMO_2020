//
// Created by Sergey Fedorov on 07/02/2020.
//

#include <stdio.h>
#include "../common_utils_string.c"

typedef struct {int men, teams;} test;

int main(){
    // 1 <= T <= 10 => max 2 sym
    int t = str_to_int(get_line(2));

    int max_fights[t];

    for(int i = 0; i < t; i++){
        // 2 <= teams <= men <= 10^4 (5 sym) => max 11 sym
        char *cur_line = get_line(11);
        char** data = str_split(cur_line, ' ');
        test cur_test = (test) {str_to_int(data[0]), str_to_int(data[1])};

        int average_man_per_team = cur_test.men / cur_test.teams;
        int teams_with_extra = (cur_test.men % cur_test.teams);
        int normal_teams = cur_test.teams - teams_with_extra;

        max_fights[i] =
                (
                    normal_teams * average_man_per_team * (cur_test.men - average_man_per_team) +
                    teams_with_extra * (average_man_per_team + 1) * (cur_test.men - (average_man_per_team + 1))
                ) / 2;
    }

    for (int i = 0; i < t; i++) {
        printf("%i\n", max_fights[i]);
    }
}