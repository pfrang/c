#include <stdio.h>
#include <conio.h>

int main(){
	int year;
	printf("Enter the year: ");
	scanf("%d", &year);
	
	if(year%4 == 0){
		printf("It's Leap Year");
	}
	else{
		printf("It's not a Leap Year");
	}
	
	return 0;
}