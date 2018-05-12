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


/**
* Definition for a binary tree node.
 */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> vec;
        if(!root)
            return vec;
        TreeNode *temp = root;
        std::stack<TreeNode *> s;
        while(temp !=NULL || !s.empty()) {
            while(temp!=NULL) {
                s.push(temp);
                temp = temp -> left;
            }
            temp = s.top();
            s.pop();
            vec.push_back(temp-> val);
            temp = temp -> right;
        }
        return vec;
    }
};


int main() {
    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right =  new TreeNode(3);
    Solution s;
    auto result =  s.inorderTraversal(root);
    for (auto i : result ) {
        cout << i << '\t';
    }
    cout << endl;
}