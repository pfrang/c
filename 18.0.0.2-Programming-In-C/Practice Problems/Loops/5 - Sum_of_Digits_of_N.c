#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main(){
	int n;
    scanf("%d", &n);
    printf("BY USING FOR-LOOP\n");
    int loop_ans = 0;
    int remainder;
    for(int i=1;i<=n;i++){
        loop_ans += i;
    }
    printf("By Loop answer is : %d", loop_ans);
    printf("\n");
    printf("BY USING NORMAL FORMULAE\n");
    int normal_ans = (n*(n+1))/2;
    printf("By formula answer is: %d", normal_ans);
}