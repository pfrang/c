#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node* top = NULL;

void linkedListTraversal(struct Node* ptr){
    while(ptr != NULL){
        printf("Element: %d\n", ptr->data);
        ptr = ptr->next;
    }
}

int isEmpty(struct Node* top){
    if(top == NULL){
        return 1;
    }
    return 0;
}

int isFull(struct Node* top){
    struct Node* p = (struct Node*) malloc (sizeof(struct Node));
    if(p == NULL){
        return 1;
    }
    return 0;
}

struct Node* push(struct Node* top, int data){
    if(isFull(top)){
        printf("Stack Overflow\n");
    }
    else{
        struct Node* newnode = (struct Node*) malloc (sizeof(struct Node));
        newnode -> data = data;
        newnode -> next = top;
        top = newnode;
        return top;
    }
}

int pop(struct Node* element){
    if(isEmpty(element)){
        printf("Stack Underflow\n");
    }
    else{
        struct Node* storing_element = element; // 30, address
        top = element -> next;
        int X_data = storing_element -> data; // data = 30
        free(storing_element); // 30 is free
        return X_data; // 30
    }
}

int main(){
    top = push(top,10); // top, 10
    top = push(top,20);
    top = push(top,30);
    printf("-------BEFORE POPPING---------\n");
    linkedListTraversal(top); // top

    int remove_element = pop(top);
    printf("-------AFTER POPPING---------\n");
    printf("Popped Element is : %d\n", remove_element);
    linkedListTraversal(top);
    return 0;
}