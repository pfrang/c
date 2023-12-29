#include <stdio.h>
#include <conio.h>

int main(){
	double millimeter;
	printf("Enter the Millimiter: ");
	scanf("%lf", &millimeter);
	double ans = (millimeter / 25.4);
	printf("Inches is: %lf", ans);
	return 0;
}