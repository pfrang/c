#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

void linkedListTraversal(struct Node *head){
    struct Node *ptr = head;
    do{
        printf("Element is %d\n", ptr->data);
        ptr = ptr->next;
    }while(ptr!=head);
}

struct Node * insertAtFirst(struct Node *head, int data){
    struct Node * newNode = (struct Node *) malloc(sizeof(struct Node)); // newnode memory allocation
    newNode->data = data;

    struct Node * p = head->next; // pointer for traversing
    while(p->next != head){ // traversing loop
        p = p->next;
    }
    // At this point p points to the last node of this circular linked list
 
    p->next = newNode;
    newNode->next = head;
    head = newNode;
    return head;
}


int main(){
    
    struct Node *head;
    struct Node *second;
    struct Node *third;
    struct Node *fourth;
 
    // Allocate memory for nodes in the linked list in Heap
    head = (struct Node *)malloc(sizeof(struct Node));
    second = (struct Node *)malloc(sizeof(struct Node));
    third = (struct Node *)malloc(sizeof(struct Node));
    fourth = (struct Node *)malloc(sizeof(struct Node));
 
    // Link first and second nodes
    head->data = 10;
    head->next = second;
 
    // Link second and third nodes
    second->data = 20;
    second->next = third;
 
    // Link third and fourth nodes
    third->data = 30;
    third->next = fourth;
 
    // Terminate the list at the third node
    fourth->data = 40;
    fourth->next = head;
 

    printf("Circular Linked list before insertion\n");
    linkedListTraversal(head);
    head = insertAtFirst(head, 50);
    head = insertAtFirst(head, 60);
    head = insertAtFirst(head, 70);
    printf("Circular Linked list after insertion\n");
    linkedListTraversal(head);
    
    return 0;
}