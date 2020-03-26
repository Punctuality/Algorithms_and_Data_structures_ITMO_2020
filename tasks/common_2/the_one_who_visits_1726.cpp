//
// Created by Sergey Fedorov on 26/03/2020.
//

#include <iostream>
#include <algorithm>

using namespace::std;

bool simple_compar(long long a, long long b){
    return a < b;
}

int main(){
    int n;
    cin >> n;

    long long xs[n];
    long long ys[n];

    for (int i = 0; i < n; ++i) {
        cin >> xs[i] >> ys[i];
    }

    long long sum = 0;

    sort(xs, xs + n, simple_compar);
    sort(ys, ys + n, simple_compar);

    for (long long i = 1; i < n; ++i) sum += ((long long) ((xs[i] - xs[i - 1]) + (ys[i] - ys[i - 1]))) *
                                             (long long) i * (long long) (n - i);


    sum = ((long long) 2) * sum / ((long long) n * (long long) (n-1)); // Need to complete ops in this order,
                                                                       // because working with integers.
                                                                       // Less rounding, the better.

    cout << sum << endl;
}