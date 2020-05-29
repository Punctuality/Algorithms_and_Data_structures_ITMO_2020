//
// Created by Sergey Fedorov on 28/05/2020.
//

#include <iostream>
#include <vector>

using namespace std;

#define INF (INT_MAX/2)

struct pipe {
    int a, b, meta_dist;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<pipe> pipes(m);

    for (int i = 0; i < m; ++i) {
        int a, b, p;
        cin >> a >> b >> p;
        pipes[i] = {a - 1, b - 1,  -p};
    }

    int start, finish;
    cin >> start >> finish;
    start--;
    finish--;

    vector<int> sum_dist(n, INF);
    sum_dist[start] = 0;

    // Bellman–Ford algorithm (without check for cycles)
    for (int i = 0; i < n - 1; ++i) for (int j = 0; j < m; ++j) {
        if (sum_dist[pipes[j].a] != INF &&
            sum_dist[pipes[j].b] > sum_dist[pipes[j].a] + pipes[j].meta_dist) {
            sum_dist[pipes[j].b] = sum_dist[pipes[j].a] + pipes[j].meta_dist;
        }
    }

    if (sum_dist[finish] != INF) cout << -sum_dist[finish]; else cout << "No solution";
}