#include <stdio.h>
#include <conio.h>

int main(){
	double P_A, rate, time;
	scanf("%lf %lf %lf", &P_A, &rate, &time);
	double first_part = (P_A * rate * time);
	double second_part = 100;
	double ans = (first_part / second_part);
	printf("Simple Interest is: %lf", ans);
	return 0;
}