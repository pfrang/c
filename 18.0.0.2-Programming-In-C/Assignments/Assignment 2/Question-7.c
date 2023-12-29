#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>


int main(){
    int a,b,i,gcd;
    scanf("%d %d", &a,&b);
    for(i=1; i<=a && i<=b; i++){
        if(a%i == 0 && b%i == 0){
            gcd = i;
        }
    }

    int mul = a*b;
    int lcm;
    lcm = (a*b)/gcd;
    printf("LCM: %d", lcm);
    return 0;
}