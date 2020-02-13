//
// Created by Sergey Fedorov on 08/02/2020.
//

#include "../../utils/common_utils_string.c"

int checkIfSolvable(const int cameras[8]){
    int all_sum = 0;
    for (int i = 0; i < 8; ++i) {
        all_sum += cameras[i];
    }

    return (
            all_sum % 2 == 0
            &&
            cameras[0] + cameras[2] + cameras[5] + cameras[7] == cameras[1] + cameras[3] + cameras[4] + cameras[6]
            );
}

void simpleReduce(int *first, int *second, char l_1, char l_2){
    (*first)--; (*second)--;
    printf("%c%c-\n", l_1, l_2);
}

void complexReduce(int *first, int *second, char distant) {
    (*first)--; (*second)--;
    if (distant == 'H')      printf("EA+\nBA-\nEH-\n");
    else if (distant == 'F') printf("EA+\nFE-\nDA-\n");
    else if (distant == 'C') printf("FB+\nEF-\nCB-\n");
    else if (distant == 'A') printf("FB+\nGF-\nAB-\n");
}

void reduceVertex(int *cameras, const int cur_connections[5], char *letters) {
    if (cameras[cur_connections[0]] > 0){
        int simpleDone = 0;
        for (int i = 1; i <= 3; i++) {
            if (cameras[cur_connections[i]] > 0) {
                simpleReduce(&cameras[cur_connections[0]], &cameras[cur_connections[i]], letters[cur_connections[0]], letters[cur_connections[i]]);
                simpleDone = 1;
                break;
            }
        }
        if (!simpleDone) {
            complexReduce(&cameras[cur_connections[0]], &cameras[cur_connections[4]], letters[cur_connections[4]]);
        }
    }
}

int main(){

    // 1 2 1 2 2 1 2 1
    // A B C D E F G H
    // 0 1 2 3 4 5 6 7
    int cameras[8];
    char letters[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    int connections[4][5] = {//   distant
            {1, 0, 2, 5, 7}, // B -> A, C, F | H
            {3, 0, 2, 7, 5}, // D -> A, C, H | F
            {4, 0, 5, 7, 2}, // E -> A, F, H | C
            {6, 7, 2, 5, 0}  // G -> H, C, F | A
    };

    // 7 spaces + 8 numbers [0;100] => ~ 7 * 1 + 8 * 2 = 23 sym
    char **read_symbols = str_split(get_line(23), ' ');

    for (int i = 0; i < 8; ++i) {
        cameras[i] = str_to_int(read_symbols[i]);
    }

    if (!checkIfSolvable(cameras)){
        printf("IMPOSSIBLE");
    } else {
        while(cameras[1] + cameras[3] + cameras[4] + cameras[6] > 0){
            for (int i = 0; i < 4; ++i) {
                reduceVertex(cameras, connections[i], letters);
            }
        }
    }

}
