//
// Created by Sergey Fedorov on 16/04/2020.
//

#include <iostream>
#include <algorithm>
#include <cmath>

#define PI 3.14159265

using namespace::std;

// Commented encountered problems

typedef struct {
    double angle;
    double distance; // Didn't use distance in sort
    int index;
} angle_distance;

bool comprar(angle_distance a, angle_distance b){
    if (abs(a.angle - b.angle) <= 1e-10){ // Initially compared by equality :(
        return a.distance < b.distance;
    } else {
        return a.angle < b.angle;
    }
}

//void print_angle(angle_distance a){
//    printf("Angle{%f, %f, %i}\n", a.angle, a.distance, a.index);
//}

int main() {

    int n;
    cin >> n;

     if (n > 0) {

         pair<int, int> pumpkins[n];
         for (int i = 0; i < n; ++i) {
             int x, y;
             cin >> x >> y;
             pumpkins[i] = (pair<int, int>) {x, y};
         }

         angle_distance angles[n - 1];

         for (int i = 1; i < n; ++i) {
             double x = pumpkins[i].first - pumpkins[0].first;
             double y = pumpkins[i].second - pumpkins[0].second;

             double cur_angle = atan2(y, x) * 180.0 / PI;
             double distance = sqrt(x * x + y * y);

             angles[i - 1] = (angle_distance) {cur_angle, distance, i + 1};
         }

         sort(angles, angles + n - 1, comprar);
//         for (angle_distance angle : angles) print_angle(angle);

         cout << n << endl;
         cout << '1' << endl;

        // Didn't consider having more than 180 degree difference between dots.
         int breakpoint = -1;
         for (int i = 1; i < n - 1; i++) {
             if (angles[i].angle - angles[i - 1].angle >= 180.0) {
                 breakpoint = i - 1;
                 break;
             }
         }

         if (breakpoint == -1) {
             for (int i = 0; i < n - 1; i++) {
                 cout << angles[i].index << endl;
             }
         } else {
             for (int i = breakpoint + 1; i < n - 1; i++) {
                 cout << angles[i].index << endl;
             }
             for (int i = 0; i <= breakpoint; i++) {
                 cout << angles[i].index << endl;
             }
         }
     }
}

/*
4
0 0
10 10
0 10
10 0
 */

/*
15
4 4
3 2
2 2
0 0
1 0
1 2
2 4
5 6
3 6
7 7
7 5
6 2
3 0
5 0
3 3
*/

/*
6
4 4
2 2
0 0
4 0
0 6
0 5
 */