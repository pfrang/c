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

int match(char a, char b){
    if(a == "{" && b == "}"){
        return 1;
    }
    if(a == "(" && b == ")"){
        return 1;
    }
    if(a == "[" && b == "]"){
        return 1;
    }
    return 0;
}

int MultipleParenthesis(char* exp){
    struct stack * s;
    s->size = 100;
    s->top = -1;
    s->arr = (char*)malloc(s->size * sizeof(char));// 200 bytes
    char popped_character;
    int i;
    for(i = 0; exp[i]!='\0';i++){
        if(exp[i] == "(" || exp[i] == "{" || exp[i] == "["){
            push(s, exp[i]);
        }
        else if(exp[i] == ")" || exp[i] == "}" || exp[i] == "]"){
            if(isEmpty(s)){
                return 0;
            }
            popped_character = pop(s);
            if(!match(popped_character, exp[i])){
                return 0;
            }
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
    char* exp = "[4-6]((8){(9-8)})";
    if(MultipleParenthesis(exp)){
        printf("This Parenthesis is Balanced");
    }
    else{
        printf("This Parenthesis is not Balanced");
    }
    return 0;
}