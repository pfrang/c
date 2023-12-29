#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main(){
	int n,p;
	printf("Enter the number: \n");
	scanf("%d", &n);
	printf("Enter the power: \n");
	scanf("%d", &p);
	// n^p
	// 5 ^ 2 = 25
	// 3 ^ 5 = 3*3*3*3*3 = 243
	// n^p = n*n*n*n*n...p times 
	int i;
	int ans = 0;
	for(i = 1; i<=p; i++){	
		ans = pow(n,i);
	}
	printf("Answer is: %d", ans);
	return 0;
}