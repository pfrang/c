#include <stdio.h>
#include <conio.h>


/*FUNCTION IS A BLOCK OF CODE WHICH CAN BE 
USED LATER IN (MAIN FUNCTION OR ANY OTHER FUNCTION) 
TO DO SOME TASK.
*/

void sum_void(int a, int b){
    printf("SUM is(void): %d\n", (a+b));
}

int sum_int(int a, int b){
    return (a+b);
}

int fibonacci(int n){
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

int fibo_recursion(int n){ //4
    // base case
    if(n == 0 && n < 0) return 0;
    else if(n == 1) return 1;

    // formulae
    return fibo_recursion(n-1) + fibo_recursion(n-2);
    // fibo(4-1) + fibo(4-2) => fibo(3) + fibo(2) = 1+2 = 3

    // fibo(3) => fibo(2) + fibo(1) => fibo(1) + fibo(0) + fibo(1) = 1+1 =2 
    // fibo(2) => fibo(1) + fibo(0) => 1+0 = 1

    // 0,1,1,2,3,5,8,13
}

int factorial(int n){
    if(n == 0 || n == 1) return 1;
    return n*factorial(n-1);
    // 5*factorial(4) => 5*[4*factorial(3)] => 5*[4*[3*factorial(2)]]
    // => 5*[4*[3*[2*factorial(1)]]] => 5*4*3*2*1 = 120
}

int main(){
    int a,b;
    scanf("%d %d", &a,&b);
    sum_void(a,b);
    int ans = sum_int(a,b);
    printf("SUM is(int): %d", (ans));
    return 0;   
}