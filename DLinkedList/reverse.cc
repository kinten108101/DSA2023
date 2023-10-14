#include <iostream>
#include "../Utils/utils.h"

using namespace std;

struct ListNode {
    int val;
    ListNode *left;
    ListNode *right;
    ListNode(int x = 0, ListNode *l = nullptr, ListNode* r = nullptr) : val(x), left(l), right(r) {}
};

ListNode* reverse(ListNode* head, int a, int b) {
    bool debug = false;
    
    ListNode *ret = head;
    if (a == b) return ret;
    int lower = -1, upper = -1;
    if (a < b) {
        lower = a;
        upper = b;
    } else {
        lower = b;
        upper = a;
    }
    ListNode *lower_node = head, *upper_node = nullptr;
    for (int i = 0; i < lower - 1 && lower_node != nullptr; i++) {
        lower_node = lower_node->right;
    }
    upper_node = lower_node;
    for (int i = 0; i < upper - lower && upper_node != nullptr; i++) {
        upper_node = upper_node->right;
    }
    
    for (int i = 0; i < (upper - lower) / 2; i++) {
        
        ListNode *lower_left = lower_node->left;
        if (debug) {
            if (lower_left != nullptr)
                cerr << lower_left->val << " ";
            else
                cerr << "NULL" << " ";
        }
        ListNode *lower_right = lower_node->right;
        if (debug) cerr << lower_right->val << " ";
        ListNode *upper_left = upper_node->left;
        if (debug)
            cerr << upper_left->val << " ";
        ListNode *upper_right = upper_node->right;
        if (debug) {
            if (upper_right != nullptr)
                cerr << upper_right->val << " ";
            else
                cerr << "NULL" << " ";
        }
        if (lower_left != nullptr)
            lower_left->right = upper_node;
        upper_node->left = lower_left;
        upper_node->right = lower_right;
        lower_right->left = upper_node;
        upper_left->right = lower_node;
        lower_node->left = upper_left;
        lower_node->right = upper_right;
        if (upper_right != nullptr)
            upper_right->left = lower_node;
            
        if (head == lower_node)
            ret = upper_node;
    }
    return ret;
}

ListNode *init(ListNode *list, size_t size, unordered_map<ListNode*, int>& map) {

}

int main() {
    utils::runtest("reverse", {
        []() {
            int size;
            cin >> size;
            int* list = new int[size];
            for(int i = 0; i < size; i++) {
                cin >> list[i];
            }
            int a, b;
            cin >> a >> b;
            unordered_map<ListNode*, int> nodeValue;
            ListNode* head = init(list, size, nodeValue);
            ListNode* reversed = reverse(head, a, b);
            try {
                printList(reversed, nodeValue);
            }
            catch(char const* err) {
                cout << err << '\n';
            }
            freeMem(head);
            delete[] list;
            return 0;
        }
    });
    return 0;
}