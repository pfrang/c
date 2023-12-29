#include <stdio.h>
#include <conio.h>
#include <math.h>

int fibonacci(int n){
	if(n == 0){
		return 0;
	}
	else if(n == 1){
		return 1;
	}
	else{
		return fibonacci(n-1)+fibonacci(n-2);
	}
}


int factorial(int n){
	if(n == 0){
		return 1;
	}
	else{
		return n*factorial(n-1);
	}
}


int main(){
	int n,i;
	scanf("%d", &n);
	/*
	for(i=1;i<=sankhya;i++){
		printf("%d ", fibonacci(i));
	}
	*/
	//int ans = factorial(sankhya);
	printf("PHACTORIAL: %d ", factorial(n));
	return 0;
}