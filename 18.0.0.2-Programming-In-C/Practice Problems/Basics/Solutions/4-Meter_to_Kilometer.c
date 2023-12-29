/*
Author: Rishav Tiwari
*/

#include <stdio.h>
#include <conio.h>

int main(){
	int meter;
	printf("Enter the meter:");
	scanf("%d",&meter);
	double ans;
	ans = (meter/1000);
	printf("Kilometer is: %lf", ans);
	// long float = lf used for double
	return 0;
}