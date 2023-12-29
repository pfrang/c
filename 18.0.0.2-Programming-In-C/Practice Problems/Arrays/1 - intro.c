#include <stdio.h>
#include <conio.h>

int main(){
	int n,i; // its no of elements
	scanf("%d",&n);
	int arr[n]; 
	//arr[n] = {1,2,3,4,5,6,7}; // array ka value kya hone wala hai
	// user se input lene ke liye for loop use krte hai
	printf("Taking input: \n");
	for(i=0;i<n;i++){
		scanf("%d", &arr[i]);
	}
	printf("Printing Array....: \n");
	for(i=0;i<n;i++){
		printf("%d ", arr[i]);
	}
	return 0;
}