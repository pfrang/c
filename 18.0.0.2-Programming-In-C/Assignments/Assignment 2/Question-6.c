#include<stdio.h>
#include<conio.h>
int main()
{
    int i, n;
    printf("Enter the Max Value : ");
    scanf("%d", &n);
    printf(" Odd Numbers between 1 and %d are : ");
    for(i = 1; i <= n; i++){
        if ( i % 2 != 0 ){
            printf(" %d\t", i);
        }
    }
    return 0;
}