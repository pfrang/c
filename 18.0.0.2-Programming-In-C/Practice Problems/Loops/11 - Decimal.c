#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>


int conbhert(long long int n);


int main(){
    long long int n;
    scanf("%d",&n);
    // long long int ans = conbhert(n);
    printf("Binary %d is converted to decimal is %lld", n, conbhert(n));
    return 0;
}


int conbhert(long long int n){
    int decimal = 0;
    int i = 0;
    int rem;
    while(n!=0){
        rem = n%10;
        n/=10;
        decimal = decimal + (rem * pow(2,i));
        i++;
    }
    return decimal;
}