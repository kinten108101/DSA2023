class BTNode {
    public: 
        int val; 
        BTNode *left; 
        BTNode *right; 
        BTNode() {
            this->left = this->right = nullptr;
        } 
        BTNode(int val) {
            this->val = val;
            this->left = this->right = nullptr;
        } 
        BTNode(int val, BTNode*& left, BTNode*& right) {
            this->val = val;
            this->left = left;
            this->right = right;
        } 
};

#include <tuple>

std::tuple<int, int> longestPath(BTNode *root) {
    if (!root) return std::make_tuple(0, 0);
    int left_len = 0;
    std::tuple<int, int> left_tuple = longestPath(root->left);
    left_len += std::get<0>(left_tuple);
    int right_len = 0;
    std::tuple<int, int> right_tuple = longestPath(root->right);
    right_len += std::get<0>(right_tuple);
    int left_sum = 0;
    if (root->left)
        left_sum = root->left->val;
    int right_sum = 0;
    if (root->right)
        right_sum = root->right->val;
    if (left_len > right_len) {
        return std::make_tuple(left_len + 1, std::get<1>(left_tuple) + left_sum);
    }
    else if (left_len < right_len) {
        return std::make_tuple(right_len + 1, std::get<1>(right_tuple) + right_sum);
    }
    else {
        if (left_sum > right_sum) {
            return std::make_tuple(left_len + 1, std::get<1>(left_tuple) + left_sum);
        }
        else {
            return std::make_tuple(right_len + 1, std::get<1>(right_tuple) + right_sum);
        }
    }
}

int longestPathSum(BTNode* root) {
    if (!root) return 0;
    int sum = root->val;
    std::tuple<int, int> result = longestPath(root);
    sum += std::get<1>(result);
    return sum;
}