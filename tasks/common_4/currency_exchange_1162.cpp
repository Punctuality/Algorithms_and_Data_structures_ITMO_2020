//
// Created by Sergey Fedorov on 30/05/2020.
//

#include <iostream>
#include <vector>

#define EPSILON 1e-5

using namespace std;

struct exchange_point {
    int cur_a, cur_b;
    double rab, cab;
};

int main(){
    int n, m, s;
    double v;

    cin >> n >> m >> s >> v;

    vector<exchange_point> ex_ps(2 * m);
    vector<double> currencies(n + 1, 0);

    for (int i = 0; i < 2 * m; i += 2) {
        int a, b;
        double rab, cab, rba, cba;
        cin >> a >> b >> rab >> cab >> rba >> cba;

        ex_ps[i    ] = {a, b, rab, cab};
        ex_ps[i + 1] = {b, a, rba, cba};
    }

    currencies[s] = v;

    // Need to twist the algo, to find the biggest path
    // This time just negation didn't work :(
    for (int i = 0; i < n - 1; i++) for (auto &ex_p : ex_ps)
        currencies[ex_p.cur_b] = max(currencies[ex_p.cur_b], (currencies[ex_p.cur_a] - ex_p.cab) * ex_p.rab);

    bool wealth_growth = false;
    for (auto &ex_p : ex_ps)
        wealth_growth |= (currencies[ex_p.cur_a] - ex_p.cab) * ex_p.rab > currencies[ex_p.cur_b] + EPSILON;

    if (wealth_growth) cout << "YES"; else cout << "NO";
}