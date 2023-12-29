#include <stdio.h>
#include <conio.h>

int main(){
	double feet;
	printf("Enter Feet: ");
	scanf("%lf",&feet);
	double meter = (feet / 3.28084);
	printf("Feet: %lf", meter);
	return 0;
}