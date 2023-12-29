#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main(){
    int n; 
    printf("Enter the number: ");
    scanf("%d", &n);
    int rev = 0;
    int rem;
    while(n!=0){
        rem = n%10;
        rev = (rev*10) + rem;
        n/=10;
    }
    printf("Reverse Number: %d", rev);
    return 0;
}