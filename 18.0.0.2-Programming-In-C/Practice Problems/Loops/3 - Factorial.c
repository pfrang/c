#include <stdio.h>
#include <conio.h>

// N! = n*(n-1)!

int main(){
	long long int N;
	scanf("%d", &N); // input number from the user
	long long int i;
	long long int factorial = 1;
	if((N == 0) || (N == 1)) printf("Factorial is: ", 1);
	else{
		for(i=2; i<=N; i+=1){
			factorial = factorial * i;
			// N = 3
			// factorial = 1*2 = 2
			// factorial = 2*3 = 6
			// factorial = 6
		}
		printf("Factorial is: %d", factorial);
	}
	return 0;
}