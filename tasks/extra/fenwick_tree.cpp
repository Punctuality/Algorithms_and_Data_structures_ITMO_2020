//
// Created by sdfedorov on 5/16/20.
//

#include <iostream>
#include <vector>

using namespace std;

/**
 Fenwick SUM Tree implementation

 Parametrized by typename T

 Stores mutable collections:
    * tree (lazily evaluated)
    * sub_array (array on which tree is based)

 Supported operation:
    * get_elem (takes elem from sub_array)
    * get_sum (takes sum from A to B, using summing tree)  Forces tree build
    * drop_elem (drops element from sub_array)             Affects consistency
    * insert_elem (inserts new elem into sub_array)        Affects consistency
    * update_elem (updates existing elem by DELTA)         Forces tree build

 Supported constructors:
    * T arr[], int n (series array and size)
    * vector<T>      (series array as vector)
*/
template<typename T>
class fenwick_tree {
private:
    vector<T> tree;
    vector<T> sub_array;
    bool is_consistent = false;

    void update_tree(int n, int index, int val) {
        index++;
        while (index <= n) {
            tree[index] += val;

            index += index & (-index);
        }
    }

    int get_prefix_sum(int end) {
        int sum = 0; end++;
        while (end > 0) {
            sum += this->tree[end];
            end -= end & (-end);
        }
        return sum;
    }

    void build_tree(){
        int size = this->sub_array.size();

        this->tree.resize(size + 1);
        for (int i=1; i <= size; i++) this->tree[i] = 0;
        for (int i=0; i < size; i++) this->update_tree(size, i, this->sub_array[i]);

        is_consistent = true;
    }

    void check_consistence(){
        if (!is_consistent) build_tree();
    }

public:
    explicit fenwick_tree(vector<T> arr_data){
        this->sub_array = arr_data;
    }

    explicit fenwick_tree(T arr[], int n) {
        this->sub_array = vector<T>(arr, arr + n);
    }

    int get_elem(int index){
        return this->sub_array[index];
    }

    void drop_elem(int index){
        this->is_consistent = false;
        this->sub_array.erase(sub_array.begin() + index);
    }

    void insert_elem(T new_elem, int index){
        this->is_consistent = false;
        this->sub_array.insert(this->sub_array.begin() + index, new_elem);
    }

    void update_elem(T delta, int index){
        this->check_consistence();
        this->sub_array[index] += delta;
        update_tree(this->sub_array.size(), index, delta);
    }

    void print_inner_state() {
        check_consistence();
        cout << "Tree: ";
        for(T elem: this->tree){
            cout << elem << "\t";
        } cout << endl;
        cout << "Array:\t";
        for(T elem: this->sub_array){
            cout << elem << "\t";
        } cout << endl;
        cout << "Index:\t";
        for(int index = 0; index < sub_array.size(); index++){
            cout << index << "\t";
        } cout << endl;

    }

    int get_sum(int start, int end){
        this->check_consistence();
        if (start == 0) return this->get_prefix_sum(end-1);
        else if (start > 0) return this->get_prefix_sum(end-1) - this->get_prefix_sum(start-1);
        else return -1;
    }
};


// Test
int main() {

    // LAME USAGE

    int freq[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
    //            0  1  2  3  4  5  6  7  8  9  10 11
    int n = sizeof(freq)/sizeof(freq[0]);

    fenwick_tree<int> tree = fenwick_tree<int>(freq, n);
    tree.print_inner_state();

    cout << tree.get_sum(0, 4) << endl; // 2 + 1 + 1 + 3 = 7
    cout << tree.get_sum(0, 3) << endl; // 2 + 1 + 1     = 4
    cout << tree.get_sum(3, 4) << endl; //             3 = 3

    // UPDATE (REBUILD) TREE

    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    fenwick_tree<int> mutable_tree = fenwick_tree<int>(numbers);
    mutable_tree.print_inner_state();

    cout << mutable_tree.get_sum(0, 4) << endl; // 1 + 2 + 3 + 4 = 10

    mutable_tree.drop_elem(2); // 3
    mutable_tree.print_inner_state();

    cout << mutable_tree.get_sum(0, 4) << endl; // 1 + 2 + 4 + 5 = 12

    mutable_tree.insert_elem(3, 2);
    mutable_tree.print_inner_state();

    cout << mutable_tree.get_sum(0, 4) << endl; // 1 + 2 + 3 + 4 = 10

    mutable_tree.update_elem(3, 2);
    mutable_tree.print_inner_state();

    cout << mutable_tree.get_sum(0, 4) << endl; // 1 + 2 + 6 + 4 = 13
}