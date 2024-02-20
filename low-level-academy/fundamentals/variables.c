#include <stdio.h>

#warning "Warning message"

#define PI 3.14

int main(void) {
	int personID = 0;
	{
		 int personID = 2;
	}
	printf("PI is %f", PI);
};

