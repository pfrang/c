#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct stack{
    int size;
    int top;// it is being used as indices
    int *arr;
    // int arr[100]; -> don't use in stack and queue
};

int isEmpty(struct stack *s){
    if(s->top == -1){
        return 1; // true
    }
    return 0; // false
}

int isFull(struct stack * s){
    if(s->top == s->size-1){
        return 1;
    }
    return 0;
}

/*

1. TOP IS BASICALLY A INDICES OF THE STACK
2. THE 's'  WHICH IS BEING USED IN THE TWO FUNCTIONS IS THE STACK_NAME
3. THE -> OPERATOR IS USED FOR EXTRACTING THE VALUES.
4. TOP = STACK.SIZE()-1   === STACK OVERFLOW
5. TOP = -1  === STACK UNDERFLOW
*/

void push(struct stack*s, int value){
    if(isFull(s)){
        printf("Stack Overflow");
    }
    else{
        s->top++; // s->top = s->top+1
        s->arr[s->top] = value; // stack->arr[stack->top] = value
    }
}

int pop(struct stack*s){
    if(isEmpty(s)){
        printf("Stack Underflow");
        return -1;
    }
    else{
        int value = s->arr[s->top]; // value = stack->array[stack->top ka element]
        s->top--; // indices are decreasing || stack->top = stack-top -1;
        return value;
    }
}

int peek(struct stack*s, int i){
    int value = s->top - i + 1; // [Top - i + 1]
    if(value < 0){
        printf("Not Valid");
        return -1;
    }
    else{
        return s->arr[value];
    }
}

int main(){
    struct stack* sp = (struct stack*) malloc (sizeof(struct stack));
    sp->size = 50;
    sp->top = -1;
    sp->arr = (int*) malloc(sp->size * sizeof(int));

    printf("---------Stack Created----------\n");
    printf("Before Inserting: %d\n", isFull(sp));
    printf("Before Pushing, Empty: %d\n", isEmpty(sp));

    push(sp,10);
    push(sp,20);
    push(sp,30);
    push(sp,40);
    push(sp,50);

    printf("After Inserting: %d\n", isFull(sp));
    printf("After Pushing, Empty: %d\n", isEmpty(sp));

    // 50, 40, 30, 20 ,10
    for(int i=1; i<= sp->top+1; i++){
        printf("The value at the index %d is value: %d  \n", i, peek(sp,i));
    }
    printf("Popped %d\n", pop(sp));
    return 0;
}