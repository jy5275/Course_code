/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <iostream>
#include <cstddef>
#define nullptr NULL

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* Reverse(ListNode *p) {
    ListNode *p1 = p->next, *p2 = nullptr;
    p->next = nullptr;
        
    if (p1) p2 = p1->next;
        
    while (p1 != nullptr) {
        p1->next = p;
        p = p1;
        p1 = p2;
        if (p2) p2 = p2->next;
    }
    return p;
}
