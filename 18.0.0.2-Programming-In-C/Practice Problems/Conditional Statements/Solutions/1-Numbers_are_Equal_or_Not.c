#include <stdio.h>
#include <conio.h>

int main(){
	int a,b;
	printf("Enter A: \n");
	scanf("%d",&a);
	printf("Enter B: \n");
	scanf("%d",&b);
	
	if(a == b){
		printf("They are equal");
	}
	else{
		printf("They are not equal");
	}
	return 0;
}