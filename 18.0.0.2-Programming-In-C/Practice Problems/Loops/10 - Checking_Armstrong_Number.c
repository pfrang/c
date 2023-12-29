#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    long long int original_num;
    scanf("%lld",&original_num);
    long long int temp = original_num;
    int rem = 0;
    int ans = 0;
    // 0
    while(temp != 0){ // 0!=0 
        rem = temp % 10; //1
        ans += (rem * rem * rem); //1*1*1, temp->1
        temp /= 10; // 1
    }
    if(ans == original_num){ // 92!=143
        printf("IT'S A ARMSTRONG NUMBER");
    }
    else{
        printf("IT'S NOT A ARMSTRONG NUMBER");
    }
    // ans = 27+64+1 = 92
    return 0;
}