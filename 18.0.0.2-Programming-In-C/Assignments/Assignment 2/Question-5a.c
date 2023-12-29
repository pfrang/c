#include <stdio.h>
#include <conio.h>

int main() {
    int n = 12;
    int i;
    int count = 0;

    for(i=1; i<=n; i++){
        if(n % i == 0)
            count++;
    }

    if(count > 2)
        printf("It’s composite: %d", n);
    else
        printf("It’s not composite: %d", n);
    return 0;
}