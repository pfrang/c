#include <stdio.h>
#include <conio.h>

int main() {
    int a, n, d, tn, i;
    int sum = 0;

    printf("Enter First Number of an A.P:" );
    scanf("%d", &a);
    printf("Total Numbers in A.P : ");
    scanf("%d", &n);
    printf("Enter the Common Difference:");
    scanf("%d", &d);

    sum = (n * (2 * a + (n - 1) * d)) / 2;
    tn = a + (n - 1) * d;
    printf("\n The Sum of Series A.P. : ");
    for(i = a; i <= tn; i = i + d)
    {
        if(i != tn)
            printf("%d ", i);
        else
            printf("%d = %d", i, sum);
    }
    return 0;
}