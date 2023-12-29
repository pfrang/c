#include <stdio.h>
#include <conio.h>

int main(){
	double meter;
	printf("Enter Meter: ");
	scanf("%lf",&meter);
	double feet = (meter * 3.28084);
	printf("Feet: %lf", feet);
	return 0;
}