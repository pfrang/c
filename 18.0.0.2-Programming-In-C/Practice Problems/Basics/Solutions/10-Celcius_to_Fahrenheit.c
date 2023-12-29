#include <stdio.h>
#include <conio.h>

int main(){
	double celcius, farenheit;
	printf("Enter the celcius: ");
	scanf("%lf", &celcius);
	double part1 = (9*celcius)/5;
	double part2 = (32);
	double ans = (part1+part2);
	printf("Farenheit is: %lf", ans);
	return 0;
}