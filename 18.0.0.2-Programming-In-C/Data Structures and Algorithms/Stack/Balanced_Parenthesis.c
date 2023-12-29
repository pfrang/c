#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct stack{
    int size;
    int top;// it is being used as indices
    char *arr;
    // int arr[100]; -> don't use in stack and queue
};

int isEmpty(struct stack *s){
    if(s->top == -1){
        return 1; // true
    }
    else{
        return 0; // false
    }
}

int isFull(struct stack * s){
    if(s->top == s->size-1){
        return 1;
    }
    else{
        return 0; // false
    }
}

void push(struct stack* s, char value){
    if(isFull(s)){
        printf("Stack Overflow!!!, Cannot push %d to the stack\n", value);
    }
    else{
        s->top++; // s->top = s->top+1
        s->arr[s->top] = value; // stack->arr[stack->top] = value
    }
}

char pop(struct stack*s){
    if(isEmpty(s)){
        printf("Stack Underflow");
        return -1;
    }
    else{
        char value = s->arr[s->top]; // value = stack->array[stack->top ka element]
        s->top--; // indices are decreasing || stack->top = stack-top -1;
        return value;
    }
}

int BalancedParenthesis(char* expression){
    struct stack * s;
    s->size = 100;
    s->top = -1;
    s->arr = (char*)malloc(s->size * sizeof(char));// 200 bytes
    int i;
    for(i = 0; expression[i]!='\0';i++){
        if( expression[i] == '(' ){
            push(s, '(');
        }
        else if( expression[i] == ')' ){
            if(isEmpty(s)){
                return 0;
            }
            pop(s);
        }
    }

    if(isEmpty(s)){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    char* exp = "((8)(*--$$9))";
    if(BalancedParenthesis(exp)){
        printf("Parenthesis are Balanced");
    }
    else{
        printf("Parenthesis are NOT Balanced");
    }
    return 0;
}