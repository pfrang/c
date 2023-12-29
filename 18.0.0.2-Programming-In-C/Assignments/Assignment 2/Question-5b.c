#include <stdio.h>
#include <conio.h>

int main()
{
    int i, n, count = 0;
    printf("Enter any number = ");
    scanf("%d", &n);
    for (i = 2; i <= n/2; i++){
        if(n%i == 0)
            count++;
            break;
    }
    if(count == 0 && n != 1){
        printf("It is a Prime Number");
    }
    else{
        printf("It is not a Prime Number");
    }
    return 0;
}