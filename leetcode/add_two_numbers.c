// Input: l1 = [2,4,3], l2 = [5,6,4]
// Output: [7,0,8]
// Explanation: 342 + 465 = 807.
// Example 2:
//
// Input: l1 = [0], l2 = [0]
// Output: [0]
// Example 3:
//
// Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
// Output: [8,9,9,9,0,0,0,1]

#include <stdlib.h>
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {}

int main() {
    struct ListNode *head;
    struct ListNode *one = NULL;
    struct ListNode *two = NULL;
    struct ListNode *three = NULL;

    /* Allocate memory */
    one = malloc(sizeof(struct ListNode));
    two = malloc(sizeof(struct ListNode));
    three = malloc(sizeof(struct ListNode));

    /* Assign data values */
    one->val = 1;
    two->val = 2;
    three->val = 3;

    /* Save address of first node in head */
    head = one;
    /* Connect nodes */
    one->next = two;
    two->next = three;
    three->next = NULL;

    // Create two linked lists (1 -> 2 -> 3 and 4 -> 5 -> 6)
    ListNode *l1 = malloc(sizeof(ListNode));
    l1->val = 1;
    l1->next = malloc(sizeof(ListNode));
    l1->next->val = 2;
    l1->next->next = malloc(sizeof(ListNode));
    l1->next->next->val = 3;
    l1->next->next->next = NULL;

    ListNode *l2 = malloc(sizeof(ListNode));
    l2->val = 4;
    l2->next = malloc(sizeof(ListNode));
    l2->next->val = 5;
    l2->next->next = malloc(sizeof(ListNode));
    l2->next->next->val = 6;
    l2->next->next->next = NULL;
}
