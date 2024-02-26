#include <stdio.h>

int main() {
	int temp;
	printf("What temp is it?");
	scanf("%d", &temp);

	if(temp >= 70) {
	 	printf("Dang thats hpt\n");
	} else if (temp >= 30 && temp < 70) {
	 	printf("Dang, its mild \n");
	} else {
  	 	printf("Dang its col\n");
	}

	printf("What");
	printf("Redo with ctrl r");
	return 0;
};

