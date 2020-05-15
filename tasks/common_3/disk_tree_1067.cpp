//
// Created by Sergey Fedorov on 07/05/2020.
//
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>

using namespace::std;

template<typename T>
class Tree {
public:
        T value;
        map<T, Tree<T>> children;

        explicit Tree(T single_value){
            this->value = single_value;
            this->children = {};
        }

        Tree() = default;

        void add_sub_tree(Tree<T> tree){
            children.insert({tree.value, tree});
        }

        void print_tree(int offset = 0){
            if (!value.empty()) cout << string(offset++, ' ') + value << endl;
            for(pair<T, Tree<T>> child : children){
                child.second.print_tree(offset);
            }
        }
};

int main(){

    int n;
    cin >> n;

    Tree<string> root = Tree<string>();

    const char delim[] = "\\";

    for(int i = 0; i < n; ++i) {
        string next_path;
        cin >> next_path;
        char to_split[next_path.size()];
        strcpy(to_split, next_path.c_str());
        char* split = strtok(to_split, delim);

        Tree<string>* workTree = &root;
        while(split != nullptr){
            auto f = workTree->children.find(string(split));
            if (f == workTree->children.end()){
                Tree<string> new_tree = Tree<string>(string(split));
                workTree->add_sub_tree(new_tree);
                workTree = &workTree->children.find(string(split))->second;
            } else {
                workTree = &f->second;
            }
            split = strtok(nullptr, delim);
        }
    }

    root.print_tree(0);
}
