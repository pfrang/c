#include <stdio.h>
#include <conio.h>

int main()
{
	//loop counter or a variable that
	//will store initial alphabet,
	//from where we will print the alphabets
	char alphabet;
	//assigning 'A' as initial alphabet
	alphabet='A';

	//print statement
	printf("Uppercase alphabets:\n");

	//loop statement, that will check the condition
	//and print the alphabets from 'A' to 'Z'
	while(alphabet<='Z')
	{
		//printing the alphabets
		printf("%c ",alphabet);
		//increasing the value by 1
		alphabet++;
	}
	return 0;
}