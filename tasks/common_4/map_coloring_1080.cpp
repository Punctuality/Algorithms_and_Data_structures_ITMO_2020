//
// Created by Sergey Fedorov on 28/05/2020.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int START_COLOR = 0;

bool btf(int root, vector<vector<int>> &edge, vector<int> &color) {
    queue<int> to_visit;

    to_visit.push(root);
    color[root] = START_COLOR;

    bool finished = false;
    bool success = true;

    while (!to_visit.empty() && !finished) {
        int from = to_visit.front(); to_visit.pop();

        for (int i = 0; i < edge[from].size(); i++) {
            int to = edge[from][i];

            if (color[from] == color[to]) {
                success = false;
                finished = true;
            } else if (color[to] == -1) {
                color[to] = !color[from];
                to_visit.push(to);
            }
        }
    }

    return success;
}

int main(){
    int n; cin >> n;
    vector<int> colors(n, -1);
    vector<vector<int>> borders(n);

    for (int a = 0; a < n; a++) {
        int b;
        cin >> b;
        while (b != 0) {
                b--;
                borders[a].push_back(b);
                borders[b].push_back(a);
                cin >> b;
        }
    }

    bool success = true;
    for (int i = 0; i < n; i++) if (colors[i] == -1) {
        bool result = btf(i, borders, colors);
        success &= result;
        if (!result) break;
    }

    if (success) {
        for (int i = 0; i < n; i++) cout << colors[i];
    } else {
        cout << "-1";
    }
}