/*
Swap two varibles values without third variable
*/

#include <stdio.h>
#include <conio.h>

int main(){
	int x,y,c;
	printf("Enter the value of A: ");
	scanf("%d",&x);
	printf("Enter the value of B: ");
	scanf("%d",&y);

	//logic for swap
	x = x+y;
	y = x-y;
	x = x-y;

	printf("Now A = %d and B = %d\n", x,y);
	return 0;
}
