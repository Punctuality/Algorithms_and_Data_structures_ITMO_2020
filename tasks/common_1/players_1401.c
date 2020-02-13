//
// Created by Sergey Fedorov on 13/02/2020.
//

#include "../../utils/common_utils_string.c"

#include <math.h>

typedef struct{
    int _1, _2;
} tuple_2;

int fig_atom = 0;

void printMatrix(int width, int height, int **matrix){
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            printf("%i", matrix[y][x]);
            if (x != width - 1){
                printf(" ");
            }
        }
        printf("\n");
    }
}

void generateMatrix(int **currentMatrix, tuple_2 range_x, tuple_2 range_y, tuple_2 ex_point){
    fig_atom++;
    int x_len = range_x._2 - range_x._1;
    int y_len = range_y._2 - range_y._1;

    int middle_coord_x = range_x._1 + (x_len) / 2;
    int middle_coord_y = range_y._1 + (y_len) / 2;

    int is_smallest = (x_len <= 2 || y_len <= 2) ? 1 : 0;

    if /*left_top_quarter*/          (ex_point._1 <= middle_coord_x && ex_point._2 <= middle_coord_y) {
        currentMatrix[middle_coord_x+1][middle_coord_y] = fig_atom;
        currentMatrix[middle_coord_x][middle_coord_y+1] = fig_atom;
        currentMatrix[middle_coord_x+1][middle_coord_y+1] = fig_atom;

        if (is_smallest) return;

        generateMatrix(currentMatrix, (tuple_2) {range_x._1, middle_coord_x}, (tuple_2) {range_y._1, middle_coord_y}, ex_point);

        generateMatrix(currentMatrix, (tuple_2) {range_x._1, middle_coord_x}, (tuple_2) {middle_coord_y + 1, range_y._2}, (tuple_2) {middle_coord_x, middle_coord_y + 1});
        generateMatrix(currentMatrix, (tuple_2) {middle_coord_x + 1, range_x._2}, (tuple_2) {range_y._1, middle_coord_y}, (tuple_2) {middle_coord_x + 1, middle_coord_y});
        generateMatrix(currentMatrix, (tuple_2) {middle_coord_x + 1, range_x._2}, (tuple_2) {middle_coord_y + 1, range_y._2}, (tuple_2) {middle_coord_x + 1, middle_coord_y + 1});
    } else if /*left_bottom_quarter*/ (ex_point._1 <= middle_coord_x && ex_point._2 > middle_coord_y) {
        currentMatrix[middle_coord_x][middle_coord_y] = fig_atom;
        currentMatrix[middle_coord_x+1][middle_coord_y] = fig_atom;
        currentMatrix[middle_coord_x+1][middle_coord_y+1] = fig_atom;

        if (is_smallest) return;

        generateMatrix(currentMatrix, (tuple_2) {range_x._1, middle_coord_x}, (tuple_2) {middle_coord_y + 1, range_y._2}, ex_point);

        generateMatrix(currentMatrix, (tuple_2) {range_x._1, middle_coord_x}, (tuple_2) {range_y._1, middle_coord_y}, (tuple_2) {middle_coord_x, middle_coord_y});
        generateMatrix(currentMatrix, (tuple_2) {middle_coord_x + 1, range_x._2}, (tuple_2) {range_y._1, middle_coord_y}, (tuple_2) {middle_coord_x + 1, middle_coord_y});
        generateMatrix(currentMatrix, (tuple_2) {middle_coord_x + 1, range_x._2}, (tuple_2) {middle_coord_y + 1, range_y._2}, (tuple_2) {middle_coord_x + 1, middle_coord_y + 1});
    } else if /*right_top_quarter*/   (ex_point._1 > middle_coord_x && ex_point._2 <= middle_coord_y) {
        currentMatrix[middle_coord_x][middle_coord_y] = fig_atom;
        currentMatrix[middle_coord_x][middle_coord_y+1] = fig_atom;
        currentMatrix[middle_coord_x+1][middle_coord_y+1] = fig_atom;

        if (is_smallest) return;

        generateMatrix(currentMatrix, (tuple_2) {middle_coord_x + 1, range_x._2}, (tuple_2) {range_y._1, middle_coord_y}, ex_point);

        generateMatrix(currentMatrix, (tuple_2) {range_x._1, middle_coord_x}, (tuple_2) {range_y._1, middle_coord_y}, (tuple_2) {middle_coord_x, middle_coord_y});
        generateMatrix(currentMatrix, (tuple_2) {range_x._1, middle_coord_x}, (tuple_2) {middle_coord_y + 1, range_y._2}, (tuple_2) {middle_coord_x, middle_coord_y + 1});
        generateMatrix(currentMatrix, (tuple_2) {middle_coord_x + 1, range_x._2}, (tuple_2) {middle_coord_y + 1, range_y._2}, (tuple_2) {middle_coord_x + 1, middle_coord_y + 1});
    } else if /*right_bottom_quarter*/ (ex_point._1 > middle_coord_x && ex_point._2 > middle_coord_y) {
        currentMatrix[middle_coord_x][middle_coord_y] = fig_atom;
        currentMatrix[middle_coord_x+1][middle_coord_y] = fig_atom;
        currentMatrix[middle_coord_x][middle_coord_y+1] = fig_atom;

        if (is_smallest) return;

        generateMatrix(currentMatrix, (tuple_2) {middle_coord_x + 1, range_x._2}, (tuple_2) {middle_coord_y + 1, range_y._2}, ex_point);

        generateMatrix(currentMatrix, (tuple_2) {range_x._1, middle_coord_x}, (tuple_2) {range_y._1, middle_coord_y}, (tuple_2) {middle_coord_x, middle_coord_y});
        generateMatrix(currentMatrix, (tuple_2) {range_x._1, middle_coord_x}, (tuple_2) {middle_coord_y + 1, range_y._2}, (tuple_2) {middle_coord_x, middle_coord_y + 1});
        generateMatrix(currentMatrix, (tuple_2) {middle_coord_x + 1, range_x._2}, (tuple_2) {range_y._1, middle_coord_y}, (tuple_2) {middle_coord_x + 1, middle_coord_y});
    }
}

int main(){
    int n = str_to_int(get_line(1));
    int two_to_n = (int) pow(2, n);

    // 512 512 => max 7 sym
    char **coords = str_split(get_line(7), ' ');
    tuple_2 point = {str_to_int(coords[0]) - 1, str_to_int(coords[1]) - 1};

    int **result = malloc(two_to_n * sizeof(int *));
    for (int i = 0; i < two_to_n; ++i) result[i] = calloc(two_to_n, sizeof(int));

    generateMatrix(result, (tuple_2) {0, two_to_n-1}, (tuple_2) {0, two_to_n-1}, point);

    printMatrix(two_to_n, two_to_n, result);
}