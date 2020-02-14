//
// Created by Sergey Fedorov on 14/02/2020.
//

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace::std;

typedef struct {
    double angle;
    int index;
} rel_point;

bool rel_point_compar(rel_point a, rel_point b){
    return a.angle < b.angle;
}

int main(){
    int n;
    cin >> n;

    //                 x ->      y ->      index
    int left_dot[3] = {99999999, 99999999, 0};

    int dots[n][2];
    for (int i = 0; i < n; ++i) {
        cin >> dots[i][0] >> dots[i][1];

        if (left_dot[0] > dots[i][0]) {
            left_dot[0] = dots[i][0]; left_dot[1] = dots[i][1]; left_dot[2] = i;
        }
    }

    rel_point angles[n-1];
    int k = 0;

    for (int i = 0; i < n; ++i) if (i != left_dot[2]) {
        double x = dots[i][0] - left_dot[0];
        double y = dots[i][1] - left_dot[1];

        angles[k++] = {atan(y/x), i};
    }

    sort(angles, angles + n - 1, rel_point_compar);

    cout << left_dot[2]+1 << ' ' << angles[(n-1)/2].index+1 << endl;
}