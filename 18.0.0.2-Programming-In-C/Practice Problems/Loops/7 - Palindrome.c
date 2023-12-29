#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d",&n);
    int temp = n;
    int rem = 0;
    int rev;
    while(n != 0){
        rem = n%10;
        rev = rev*10 + rem;
        n/=10;
    }

    if(temp == rev){
        printf("Palindrome hai");
    }
    else{
        printf("Palindrome NHI hai");
    }
    return 0;
}