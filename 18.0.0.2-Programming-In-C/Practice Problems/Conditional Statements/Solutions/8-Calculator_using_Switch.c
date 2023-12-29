#include <stdio.h>
#include <conio.h>

int main(){
	int a,b;
	char op;
	
	printf("Enter Operator: ");
	scanf("%c", &op);
	
	printf("Enter A: ");
	scanf("%d",&a);
	
	printf("Enter B: ");
	scanf("%d",&b);

	
	switch(op){
		case '+':
			printf("SUM is: %d", (a+b));
			break;
		
		case '-':
			printf("Diff is: %d", (a-b));
			break;
		
		case '*':
			printf("Mul is: %d", (a*b));
			break;
		
		case '/':
			printf("Div is: %d", (a/b));
			break;
		
		default:
			printf("Invalid Input");
			break;
	}
	return 0;
}