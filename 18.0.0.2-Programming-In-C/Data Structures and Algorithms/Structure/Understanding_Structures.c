#include <stdio.h>
#include <conio.h>

struct student{
	int roll;
	int age;
	char name[100];
};

int main(){
	struct student Rishav;
	/*  We can't access the struct part by %d. 
		It can be access by "dot(.) operator"
	*/
	Rishav.roll = 128;
	Rishav.age = 19;
	printf("Rishav Tewari Roll Number is: %d", Rishav.roll);
	return 0;
}
