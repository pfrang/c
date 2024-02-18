#include <stdio.h>

#define MAX_PERSONS 1024

// #define DEBUG
// Can also be defined with the -D flag with gcc so gcc path -DDEBUG would also create


/* Compilation process
# - Preprocessor
# - Compilation
*/

int main() {

	#ifdef DEBUG
	printf("WE ARE IN DEBUG MODE: %s:%d", __FILE__, __LINE__);
	#endif

	return 0;
};
