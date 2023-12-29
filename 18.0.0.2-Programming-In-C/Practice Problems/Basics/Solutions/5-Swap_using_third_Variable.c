/*
Swap two Variable’s values using Third variable
*/

#include <stdio.h>
#include <conio.h>


int main(){
	int a,b,c;
	printf("Enter the value of A: ");
	scanf("%d",&a);
	printf("Enter the value of B: ");
	scanf("%d",&b);
	
	//logic for swap
	c = a;
	a = b;
	b = c;
	
	printf("Now A = %d and B = %d\n", a,b);
	return 0;
}