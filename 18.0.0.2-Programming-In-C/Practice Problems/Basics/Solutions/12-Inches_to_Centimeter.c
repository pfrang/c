#include <stdio.h>
#include <conio.h>

int main(){
	double inches;
	printf("Enter the inches: ");
	scanf("%d", &inches);
	double ans = (inches * 2.54);
	printf("Centimeter is: %d", ans);
	return 0;
}