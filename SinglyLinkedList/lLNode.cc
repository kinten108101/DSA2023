#include <iostream>
#include <string>
#include "../Utils/utils.h"

class LLNode {
public:
    static void printList(LLNode* from);
    static LLNode* createWithIterators(int *start, int *end);
public:
    int val;
    LLNode* next;
    LLNode();
    LLNode(int val, LLNode* next);
    void clear();
private:
    void _clear_recursive();
};

void LLNode::printList(LLNode *from) {
    std::string str("");
    str += "[";
    for (LLNode *p = from; p != nullptr; p = p->next) {
        if (p == from) str += std::to_string(p->val);
        else str += ", " + std::to_string(p->val);
    }
    str += "]";
    std::cout << str << std::endl;
}

LLNode *LLNode::createWithIterators(int *start, int *end) {
    LLNode *node = new LLNode();
    LLNode *next = nullptr;
    for (int *p = end - 1; p >= start; p--) {
        if (node != nullptr) next = node;
        node = new LLNode(*p, next);
    }
    return node;
}

LLNode::LLNode(): val(0), next(nullptr) {}
LLNode::LLNode(int val, LLNode *next): val(val), next(next) {}

void LLNode::clear() {
    this->_clear_recursive();
    this->next = nullptr;
}

void LLNode::_clear_recursive() {
    if (this->next == nullptr) return;
    this->next->_clear_recursive();
    delete this->next;
}

LLNode* reverseLinkedList(LLNode* head) {
    LLNode *p = head, *prev = nullptr;
    for (; p != nullptr;) {
        LLNode *_next = p->next;
        p->next = prev;
        prev = p;
        p = _next;
    }
    return prev;
}

LLNode* addLinkedList(LLNode* l0, LLNode* l1) {
    std::vector<int> vals;
    LLNode *cur_top = l0;
    LLNode *cur_bottom = l1;
    bool carry = false;
    while (cur_top != nullptr || cur_bottom != nullptr || carry) {
        int sum = 0;
        if (cur_top != nullptr)
            sum += cur_top->val;
        if (cur_bottom != nullptr)
            sum += cur_bottom->val;
        sum += carry;

        int val = -1;
        if (sum >= 10) {
            val = sum - 10;
            carry = true;
        } else {
            val = sum;
            carry = false;
        }
        vals.push_back(val);

        if (cur_top != nullptr) cur_top = cur_top->next;
        if (cur_bottom != nullptr) cur_bottom = cur_bottom->next;
    }

    LLNode *node = nullptr;
    LLNode *next = nullptr;
    for (auto it = vals.end() - 1; it != vals.begin() - 1; it--) {
        if (node != nullptr) next = node;
        node = new LLNode(*it, next);
    }
    return node;
}

int main() {
    utils::runtest("Operation: Reverse Singly Linked List", {
        []() {
            int arr[] = {13, 88, 60, 7, 192};
            LLNode* head = LLNode::createWithIterators(arr, arr + sizeof(arr) / sizeof(int));
            LLNode::printList(head);
            std::cout << "\n";
            LLNode* newhead = reverseLinkedList(head);
            LLNode::printList(newhead);
            newhead->clear();

            return 0;
        },
        []() {
            int arr[] = {31, 22, 46, 152, 14, 87, 196, 97, 5, 93};
            LLNode* head = LLNode::createWithIterators(arr, arr + sizeof(arr) / sizeof(int));
            LLNode::printList(head);
            std::cout << "\n";
            LLNode* newhead = reverseLinkedList(head);
            LLNode::printList(newhead);
            newhead->clear();

            return 0;
        },
        []() {
            int arr[] = {104, 50, 154, 40, 15, 171, 56, 114, 67, 90, 46, 179, 152, 177, 139, 45, 18, 55, 38, 158, 8, 157, 143, 37, 16, 83, 173, 82, 156, 51, 124, 25, 68, 51, 194, 105, 44, 17, 97, 0, 150, 66, 71, 81, 11, 180, 148, 160, 127, 93, 108, 13, 122, 172, 39, 88, 62, 38, 61, 156, 45, 131, 69, 191, 123, 42, 103, 56, 69, 138, 185, 162, 192, 147, 71, 80, 12, 36, 191, 121, 194, 86, 92, 183, 164, 97, 185, 130, 29, 174, 112, 194, 185, 132, 27, 197, 158, 151, 51, 174};
            LLNode* head = LLNode::createWithIterators(arr, arr + sizeof(arr) / sizeof(int));
            LLNode::printList(head);
            std::cout << "\n";
            LLNode* newhead = reverseLinkedList(head);
            LLNode::printList(newhead);
            newhead->clear();
            return 0;
        },
    });
    utils::runtest("Add Two Linked Lists", {
        []() {
            int arr1[] = {2, 9};
            int arr2[] = {0, 5};
            LLNode* head1 = LLNode::createWithIterators(arr1, arr1 + sizeof(arr1) / sizeof(int));
            LLNode* head2 = LLNode::createWithIterators(arr2, arr2 + sizeof(arr2) / sizeof(int));
            LLNode* newhead = addLinkedList(head1, head2);
            LLNode::printList(newhead);
            head1->clear();
            head2->clear();
            newhead->clear();
            return 0;
        },
        []() {
            int arr1[] = {};
            int arr2[] = {};
            LLNode* head1 = LLNode::createWithIterators(arr1, arr1 + sizeof(arr1) / sizeof(int));
            LLNode* head2 = LLNode::createWithIterators(arr2, arr2 + sizeof(arr2) / sizeof(int));
            LLNode* newhead = addLinkedList(head1, head2);
            LLNode::printList(newhead);
            head1->clear();
            head2->clear();
            newhead->clear();
            return 0;
        },
        []() {
            int arr1[] = {2, 6, 7, 8, 9};
            int arr2[] = {2, 8};
            LLNode* head1 = LLNode::createWithIterators(arr1, arr1 + sizeof(arr1) / sizeof(int));
            LLNode* head2 = LLNode::createWithIterators(arr2, arr2 + sizeof(arr2) / sizeof(int));
            LLNode* newhead = addLinkedList(head1, head2);
            LLNode::printList(newhead);
            head1->clear();
            head2->clear();
            newhead->clear();
            return 0;
        },
        []() {
            int arr1[] = {8, 7, 2, 5, 5, 9, 7, 9, 0, 5, 7, 1, 6, 9, 9, 4, 1, 7, 7, 3};
            int arr2[] = {5, 2, 4, 8, 0, 0};
            LLNode* head1 = LLNode::createWithIterators(arr1, arr1 + sizeof(arr1) / sizeof(int));
            LLNode* head2 = LLNode::createWithIterators(arr2, arr2 + sizeof(arr2) / sizeof(int));
            LLNode* newhead = addLinkedList(head1, head2);
            LLNode::printList(newhead);
            head1->clear();
            head2->clear();
            newhead->clear();

            return 0;
        },
    });
    return 0;
}