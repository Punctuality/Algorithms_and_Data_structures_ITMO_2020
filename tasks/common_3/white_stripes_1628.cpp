//
// Created by Sergey Fedorov on 07/05/2020.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace::std;

bool comp_weeks(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first) {
        return a.first < b.first;
    } else {
        return a.second < b.second;
    }
}

bool comp_days(pair<int, int> a, pair<int, int> b) {
    if (a.second != b.second) {
        return a.second < b.second;
    } else {
        return a.first < b.first;
    }
}

int main() {
    int m, n, k, result = 0;
    cin >> m >> n >> k;

    if (m == 0 || n == 0) {
        return 0;
    }

    vector<pair<int, int>> points;
    vector<pair<int, int>> squares;

    // Given dots

    for (int i = 0; i < k; ++i) {
        pair<int, int> p;
        cin >> p.first >> p.second;
        p.first--;
        p.second--;
        points.push_back(p);
    }

    // Vertical and horizontal borders

    for (int i = 0; i < m; ++i) {
        pair<int, int> p = {i, -1};
        pair<int, int> p2 = {i, n};
        points.push_back(p2);
        points.push_back(p);
    }

    for (int i = 0; i < n; ++i) {
        pair<int, int> p = {-1, i};
        pair<int, int> p2 = {m, i};
        points.push_back(p2);
        points.push_back(p);
    }

    // Counting long boxes

    // Horizontal
    sort(points.begin(), points.end(), comp_days);
    for (int i = 0; i < points.size() - 1; ++i) {
        if (points[i].second == points[i + 1].second) {
            int length = points[i + 1].first - points[i].first - 1;
            if (length == 1){
                squares.push_back((pair<int, int>) {points[i].first + 1, points[i].second});
            } else if (length > 1) result++;

        }
    }

    // Vertical
    sort(points.begin(), points.end(), comp_weeks);
    for (int i = 0; i < points.size() - 1; ++i) {
        if (points[i].first == points[i + 1].first) {
            int height = points[i + 1].second - points[i].second - 1;
            if (height == 1){
                squares.push_back((pair<int, int>) {points[i].first, points[i].second + 1});
            } else if (height > 1) result++;
        }
    }

    // Counting short boxes (just boxes)

    sort(squares.begin(), squares.end(), comp_days);
    sort(squares.begin(), squares.end(), comp_weeks);

    switch (squares.size()) {
        case 1: result++; break;
        case 0: break;
        default:
            for (int i = 0; i < squares.size() - 1; i++) {
                if (squares[i] == squares[i + 1]) {
                    result++;
                    i++;
                }
            }
    }

    cout << result << endl;
}