#include <stdio.h>
#include <conio.h>

int main(){
	int a,b,c;
	printf("Enter A: \n");
	scanf("%d",&a);
	printf("Enter B: \n");
	scanf("%d",&b);
	printf("Enter C: \n");
	scanf("%d",&c);
	
	if((a>b) && (a>c)) {
		printf("A is greatest");
	}
	
	else if((b>a) && (b>c)){
		printf("B is greatest");
	}
	
	else{
		printf("C is greatest");
	}
	
	return 0;
}