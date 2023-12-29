#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define N 100 // size

int stack[N];
int top = -1;

void push();
void pop();
void peek();
void traverseStack();

void push(){
    int element;
    printf("Enter the element");
    scanf("%d", &element);
    if(top == N-1){
        printf("Stack Overflow");
    }
    else{
        top++;
        stack[top] = element;
    }
}

void pop(){
    int target;
    if(top == -1){
        printf("Stack Underflow");
    }
    else{
        target = stack[top];
        top--;
    }
}

void peek(){
    if(top == -1){
        printf("Stack is Empty");
    }
    else{
        printf("Stack is not Empty");
    }
}

void traverseStack(){
    int i;
    for(i=top;i>=0;i++){
        printf("%d", stack[i]);
    }
}

int main(){
    int choice;
    do{
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                traverseStack();
                break;
            default:
                printf("Invalid Choice");
                break;
        }
    }while(choice!=0);
    return 0;
}