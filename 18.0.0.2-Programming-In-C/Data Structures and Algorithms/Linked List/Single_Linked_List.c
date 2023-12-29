#include <stdio.h>
#include <stdlib.h> //standard library

struct node{
	int data;
	struct node* next; //storing address
};

void traverseLinkedList(struct node* ptr){
	while(ptr != NULL){
		printf("%d\n", ptr->data);
		ptr = ptr->next;
	}
}

int main(){
	struct node* head = NULL;
	struct node* second = NULL;
	struct node* third = NULL;
	struct node* fourth = NULL;
	struct node* fifth = NULL;
	
	head = (struct node*)malloc(sizeof(struct node));
	second = (struct node*)malloc(sizeof(struct node));
	third = (struct node*)malloc(sizeof(struct node));
	fourth = (struct node*)malloc(sizeof(struct node));
	fifth = (struct node*)malloc(sizeof(struct node));
	// (Head ka data type) memory allocate kro (sizeof(struct node))
	// (any_datatype) memory allocate kro [malloc] (sizeof(any_datatype))
	
	head -> data = 10;
	head -> next = second;
	
	second -> data = 20;
	second -> next = third;
	
	third -> data = 30;
	third -> next = fourth;
	
	fourth -> data = 40;
	fourth -> next = fifth;
	
	fifth -> data = 50;
	fifth -> next = NULL;
	
	printf("The Linked List is: \n");
	traverseLinkedList(head);
	return 0;
}