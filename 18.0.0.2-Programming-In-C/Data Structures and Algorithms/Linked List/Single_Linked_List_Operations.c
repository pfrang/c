#include <stdio.h>
#include <conio.h>
#include <stdlib.h> //standard library
// #include <stdbool.h>

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


struct node* add_at_beg(struct node* head, int data){
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = head;
    head = newnode;
    return head;
}

struct node * insertAtIndex(struct node *head, int data, int index){
    struct node * ptr = (struct node *) malloc(sizeof(struct node));
    struct node * p = head;
    int i = 0;
 
    while (i!=index-1)
    {
        p = p->next;
        i++;
    }
    ptr->data = data;
    ptr->next = p->next;
    p->next = ptr;
    return head;
}

struct node* add_at_end(struct node* head, int data){
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    struct node* p = head;
    newnode->data = data;
    while(p->next != NULL){
        p=p->next;
    }
    p->next = newnode;
    newnode->next = NULL;
    return head;
}

void search(struct node* head,int item){
    struct node* p =head; // pointer for traversing
    int pos=1; // position starts from 1
    while(p!=NULL){ // traversing till the pointer doesn't get the last node
        if(p->data==item){ // checking if the pointer data is equal to the target value
            printf("Item %d is found at %d position",item,pos); // if statement is true then print it
            return; // and then return
        }
        // if not
        p=p->next; // increase the pointer to next node
        pos++; // and also increase the position
    }
    printf("Item %d not found at position in following list",item); // if at last not found.
}

struct node * deleteFirst(struct node * head){
    struct node * ptr = head;
    head = head->next;
    free(ptr);
    return head;
}

struct node * deleteAtIndex(struct node * head, int index){
    struct node *p = head;
    struct node *q = head->next;
    for (int i = 0; i < index-1; i++)
    {
        p = p->next;
        q = q->next;
    }
    
    p->next = q->next;
    free(q);
    return head;
}

struct node * deleteAtLast(struct node * head){
    struct node *p = head; //p is for traversing
    struct node *q = head->next; // q is for checking last node
    while(q->next !=NULL) // q is standing at 2nd last node
    {
        p = p->next; 
        q = q->next;
    }
    
    p->next = NULL;
    free(q);
    return head;
}

int main(){
    struct node* head = NULL;
	struct node* second = NULL;
	struct node* third = NULL;


    head = (struct node*)malloc(sizeof(struct node));
	second = (struct node*)malloc(sizeof(struct node));
	third = (struct node*)malloc(sizeof(struct node));

    head -> data = 10;
	head -> next = second;
	
	second -> data = 20;
	second -> next = third;
	
	third -> data = 30;
	third -> next = NULL;

    printf("Before Inserting Linked List is: \n");
	traverseLinkedList(head);

    // printf("Insertion at the Start of the Linked List: \n");
    // head = add_at_beg(head,40);
    // traverseLinkedList(head);


    //printf("Insertion at the End of the Linked List: \n");
    head = add_at_end(head,40);
    traverseLinkedList(head);


    // printf("Search in a list: \n");
    // search(head, 40);

	return 0;
}