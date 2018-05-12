/**
 * Reverse a singly linked list.
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <list>
#include <stack>
#include <queue>

using std::priority_queue;
using std::list;
using std::map;
using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::stack;
using std::vector;

struct tree_t {
    struct tree_t *left;
    struct tree_t *right;
    struct tree_t *parent;
    int key;

    tree_t() {
        left = 0;
        right = 0;
        parent = 0;
        key = -1;
    }
};
typedef struct tree_t tree_t;
void store(int);

void print_tree(tree_t *tree) {
    tree_t *prev;
    prev = 0;

    while (tree) {
        if (prev == tree->parent) {
            store(tree->key);
            prev = tree;
            tree = tree->left  ? tree->left :
                   tree->right ? tree->right :
                   tree->parent;
        } else if (prev == tree->left && tree->right) {
            prev = tree;
            tree = tree->right;
        } else {
            prev = tree;
            tree = tree->parent;
        }
    }
}

#define MAX_SIZE 10
int keys[MAX_SIZE];
int count = 0;

void reset_storage() {
    count = 0;
}

void store(int key) {
    keys[count++] = key;
}

int main() {
    tree_t *root = new tree_t;
    root->key = 1;
    root->parent = 0;
    root->left = new tree_t;
    root->left->key = 2;
    root->left->parent = root;
    root->right = new tree_t;
    root->right->key = 3;
    root->right->parent = root;
    print_tree(root);

    for(int i = 0; i < count; i++) {l
        cout << keys[i] << '\t';
    }
    cout << endl;

}