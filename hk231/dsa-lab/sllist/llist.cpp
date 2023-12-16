#include <iostream>

using namespace std;

class LLNode {
public:
    int val;
    LLNode* next;
    LLNode() {}
    LLNode(int val, LLNode* next): val(val), next(next) {};
};

LLNode* addLinkedList(LLNode* l0, LLNode* l1) {
    if (!l0 && !l1) return nullptr;
    if (!l0) return l1;
    if (!l1) return l0;
    
    int cnt = 0;
    LLNode* tmp = new LLNode((l0->val + l1->val + cnt) % 10, nullptr);
    LLNode* head = tmp;
    if (l0->val + l1->val + cnt >= 10) cnt = 1; else cnt = 0;
    l0 = l0->next; l1 = l1->next;
    
    while (l0 != nullptr && l1 != nullptr) {
        LLNode* newNode = new LLNode((l0->val + l1->val + cnt) % 10, nullptr);
        if (l0->val + l1->val + cnt >= 10) cnt = 1; else cnt = 0;
        l0 = l0->next; l1 = l1->next;
        tmp->next = newNode;
        tmp = tmp->next;
    }

    LLNode* t = (l0 ? l0 : l1);

    while (t != nullptr) {
        LLNode* newNode = new LLNode((t->val + cnt) % 10, nullptr);
        if (t->val + cnt >= 10) cnt = 1; else cnt = 0;
        t = t->next;
        tmp->next = newNode;
        tmp = tmp->next;
    }

    if (cnt == 1) {
        tmp->next = new LLNode(1, nullptr);
    }

    return head;
}

int main() {
    LLNode* head1 = new LLNode(2, new LLNode(5, new LLNode(6, new LLNode(7, new LLNode(5, new LLNode(1, new LLNode(4, new LLNode(1, new LLNode(2, new LLNode(9, nullptr))))))))));
    LLNode* head2 = new LLNode(2, new LLNode(1, new LLNode(0, nullptr)));

    LLNode* tmp = addLinkedList(head1, head2);

    while (tmp != nullptr) {
        cout << tmp->val << ' ';
        tmp = tmp->next;
    }
}