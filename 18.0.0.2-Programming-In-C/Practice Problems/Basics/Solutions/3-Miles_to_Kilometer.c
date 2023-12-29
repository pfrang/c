/*
Author: Rishav Tiwari
*/

#include <stdio.h>
#include <conio.h>

int main(){
	double mile,answer;
	printf("Enter the Mile: ");
	scanf("%d",&mile);
	// 1 mile = 1.6km
	answer = (mile*1.6);
	printf("Kilometer(1st approach): %d\n", answer);
	// 2nd approach
	double mile1 = (mile*1600); //mt
	double answer1 = (mile1)/1000; //km
	printf("Kilometer(2nd approach): %d", answer1);
	return 0;
}