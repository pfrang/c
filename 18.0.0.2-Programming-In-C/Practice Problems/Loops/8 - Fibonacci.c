#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


int fib(int n){
    int first = 0;
    int second = 1;
    int sum,i;
    if(n == 0){
        return first;
    }
    for(i = 2; i<=n; i++){
        sum = first + second;
        first = second;
        second = sum;
    }
    return second;
}

int main(){
    int n;
    scanf("%d", &n);
    printf("Fibonacci Number: %d", fib(n));
    return 0;
}