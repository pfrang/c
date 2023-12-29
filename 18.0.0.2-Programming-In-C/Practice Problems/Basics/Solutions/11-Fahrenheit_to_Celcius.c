#include <stdio.h>
#include <conio.h>

int main(){
	double celcius, farenheit;
	printf("Enter the Farenheit: ");
	scanf("%lf", &farenheit);
	double part1 = (farenheit-32)/9;
	double part2 = (5);
	double ans = (part1*part2);
	printf("Celcius is: %lf", ans);
	return 0;
}