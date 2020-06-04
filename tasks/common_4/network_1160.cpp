//
// Created by Sergey Fedorov on 28/05/2020.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct connection {
    int a, b, length;
    bool used = false;

    connection()= default;

    connection(int a, int b, int length){
        this->a = a;
        this->b = b;
        this->length = length;
    }

};

bool connection_comprar(connection fst, connection snd){
    return fst.length < snd.length;
}

int find_parent(vector<int> &parents, int x){
    if (x != parents[x]) parents[x] = find_parent(parents, parents[x]);
    return parents[x];
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<connection> cs(m);
    vector<int> ranks(n + 1, 0);
    vector<int> parents(n + 1);
    for (int i = 0; i <= n; ++i) parents[i] = i;

    int longest_conn = 0;
    int out = 0;

    for (int i = 0; i < m; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        a--; b--;
        cs[i] = connection(a, b, l);
    }

    sort(cs.begin(), cs.end(), connection_comprar);

    for (int i = 0; i < m; ++i) {
        int point_a = cs[i].a;
        int point_b = cs[i].b;

        int parent_a = find_parent(parents, point_a);
        int parent_b = find_parent(parents, point_b);

        if (parent_a != parent_b) {
            longest_conn = max(longest_conn, cs[i].length);

            out++;
            cs[i].used = true;

            if      (ranks[parent_a] > ranks[parent_b]) parents[parent_b] = parent_a;
            else if (ranks[parent_b] > ranks[parent_a]) parents[parent_a] = parent_b;
            else if (ranks[parent_a] == ranks[parent_b]) {
                parents[parent_b] = parent_a;
                ranks[parent_a]++;
            }

        }
    }

    cout << longest_conn << endl;
    cout << out << endl;

    for (connection conn : cs) if (conn.used) cout << conn.a + 1 << " " << conn.b + 1 << endl;
}