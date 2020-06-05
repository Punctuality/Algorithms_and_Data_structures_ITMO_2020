//
// Created by Sergey Fedorov on 05/06/2020.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace::std;


#define INF (LONG_MAX/2)
#define WIDTH 10

int get_digit(long long num, int pos){
    long long denominator = 1;
    for (int i = 0; i < pos; ++i) denominator *= 10;
    return (int) (num / denominator % 10);
}

long long set_digit(long long num, int pos, int value){
    long long power = 1;
    for (int i = 0; i < pos; ++i) power *= 10;

    return  num + ((long long) value - get_digit(num, pos)) * power;
}

int prefixSimilarity(long long num_a, long long num_b){
    int matched_digits = 0;
    for (int i = WIDTH - 1; i >= 0; --i)
        if (get_digit(num_a, i) == get_digit(num_b, i)) matched_digits++; else break;
    return matched_digits;
}

struct Node {
    vector<pair<int, Node*>> vs;
    Node* parent;
    long ping_time = INF;
    bool visited;
    long long num;
    int index;
};

void record_node(
        unordered_map<long long, Node*> &map,
        vector<int> &weights, vector<Node> &nodes,
        long long node_num, int node_ind) {

    vector<pair<int, Node*>> v;

    for (int i = 0; i < WIDTH; i++) {
        for (int d = 0; d < WIDTH; d++) {
            long long changed_num = set_digit(node_num, i, d);

            if (map.find(changed_num) != map.end())
                v.emplace_back(weights[prefixSimilarity(node_num, changed_num)], (*map.find(changed_num)).second);
        }
    }

    for (int i = 0; i < WIDTH; i++) {
        for (int j = i + 1; j < WIDTH; j++) {

            long long swapped_num = set_digit(
                    set_digit(
                            node_num,
                            j,
                            get_digit(node_num, i)
                            ),
                    i,
                    get_digit(node_num, j)
                    );

            if(map.find(swapped_num) != map.end())
                v.emplace_back(weights[prefixSimilarity(node_num, swapped_num)], (*map.find(swapped_num)).second);

        }
    }

    map[node_num] = &nodes[node_ind];

    for(pair<int, Node*> p : v){
        p.second->vs.emplace_back(p.first, &nodes[node_ind] );
        nodes[node_ind].vs.emplace_back(p.first, p.second );
    }
    nodes[node_ind].num = node_num;
    nodes[node_ind].index = node_ind;
}


void shortest_path(vector<Node> &nodes){
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<>> q;

    nodes[0].ping_time = 0;

    q.push( {0, &nodes[0]} );
    while(!q.empty()) {
        pair<int, Node*> p = q.top();
        q.pop();
        Node* node = p.second;

        if (node->visited) continue;
        else node->visited = true;

        for (pair<int, Node*> &v: node->vs) {
            Node* neighbour_node = v.second;
            int neighbour_cost = v.first;

            if (!neighbour_node->visited && neighbour_node->ping_time > node->ping_time + neighbour_cost) {
                neighbour_node->parent = node;
                neighbour_node->ping_time = node->ping_time + neighbour_cost;
                q.push({neighbour_node->ping_time, neighbour_node});
            }
        }
    }
}

int main(){
    int n;
    cin >> n;

    vector<Node> nodes(n);

    vector<int> weights(WIDTH);
    for (int &weight: weights) cin >> weight;

    unordered_map<long long, Node*> map;

    for (int i = 0; i < n; i++) {
        long long num;
        cin >> num;
        record_node(map, weights, nodes, num, i);
    }

    vector<Node*> result;
    shortest_path(nodes);

    if (!nodes[n - 1].visited) {
        cout << -1;
    } else {
        cout << nodes[n - 1].ping_time << "\n";

        for (Node* node = &nodes[n - 1]; node; node = node->parent) {
            result.push_back(node);
        }

        cout << result.size() << "\n";

        for (int i = (int) result.size() - 1; i >= 0; --i) {
            cout << 1 + result[i]->index << " ";
        }
    }
}
