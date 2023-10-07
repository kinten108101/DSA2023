#include <iostream>
#include "../Utils/utils.h"

using namespace std;

struct ListNode {
    int val;
    ListNode *left;
    ListNode *right;
    ListNode(int x = 0, ListNode *l = nullptr, ListNode* r = nullptr) : val(x), left(l), right(r) {}
};

void init()

ListNode* reverse(ListNode* head, int a, int b) {
    if (a == b) return head;
    int lower = -1, upper = -1;
    if (a < b) {
        lower = a;
        upper = b;
    } else {
        lower = b;
        upper = a;
    }
    ListNode *lower_node = head, *upper_node = nullptr;
    for (int i = 0; i < lower - 1; i++) {
        lower_node = lower_node->right;
    }
    upper_node = lower_node;
    for (int i = 0; i < upper - lower; i++) {
        upper_node = upper_node->right;
    }
    for (int i = 0; i < (upper - lower) / 2; i++) {
        lower_node->left->right = upper_node;
        ListNode *tmp = upper_node->right;
        upper_node->right = lower_node->right;
        upper_node->left->right = lower_node;
        lower_node->right = tmp;

        tmp = upper_node;
        upper_node = lower_node;
        lower_node = tmp;

        upper_node = upper_node->left;
        lower_node = lower_node->right;
    }
    return head;
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