#include <stdio.h>
#include <string.h>


#define MAX_IDS 32

int main() {

	char mystr[32] = {'h', 'e', 'l', 'l', 'o', 0};

	char myotherstr[] = "yoyoyoyo 2";

	printf("%s\n", mystr);
	printf("%s\n", myotherstr);

     	strcpy(mystr , myotherstr);
	//strncpy(dest, src, n);
	printf("%s\n", mystr);
	printf("%s\n", myotherstr);


}
