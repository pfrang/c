#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
    struct node* prev;
}*head, *last;

// struct node* head;
// struct node* last;

void traverseLinkedList(struct node* ptr){
	while(ptr != NULL){
		printf("%d\n", ptr->data);
		printf("<=>");
		ptr = ptr->next;
	}
	printf("NULL");
}

void insertAtBeginning(int data){
    struct node * newNode;
    if(head == NULL){
        printf("Error, List is Empty!\n");
    }
    else{
        newNode = (struct node *)malloc(sizeof(struct node));
        newNode->data = data;
        newNode->next = head; // Point to next node which is currently head
        newNode->prev = NULL; // Previous node of first node is NULL
        /* Link previous address field of head with newnode */
        head->prev = newNode;
        /* Make the new node as head node */
        head = newNode;
        printf("NODE INSERTED SUCCESSFULLY AT THE BEGINNING OF THE LIST\n");
    }
}

void insertAtEnd(int data){
    struct node * newNode;
    if(last == NULL){
        printf("Error, List is empty!\n");
    }
    else{
        newNode = (struct node *)malloc(sizeof(struct node));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = last;
        last->next = newNode;
        last = newNode;
        printf("NODE INSERTED SUCCESSFULLY AT THE END OF LIST\n");
    }
}


int main(){
	head = NULL;
    struct node* second = NULL;

    second = (struct node*)malloc(sizeof(struct node));
    head -> data = 10;
	head -> next = second;
    head -> prev = NULL;

    second -> data = 20;
    second -> next = NULL;
    second -> prev = head;

    traverseLinkedList(head);
	return 0;
}