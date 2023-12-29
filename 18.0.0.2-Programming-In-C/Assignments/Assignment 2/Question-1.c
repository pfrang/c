#include <stdio.h>
#include <conio.h>
int main(){
    int i,n, sum=0;
    printf("Enter the Number : ");
    scanf("%d",&n);
    printf("First natural numbers{Series} are :%d \n");
    for(i=1;i<=n;i++){
        printf("%d",i);
        sum+=i;
    }
    printf("Sum of natural numbers : %d \n", sum);
    return 0;
}