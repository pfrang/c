#include <stdio.h>
#include <conio.h>

int main(){
	int n,i;
	scanf("%d",&n);
	int arr[n];
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	
	int max = arr[0];// => 1
	int min = arr[0];// => 1
	
	for(i=0;i<n;i++){
		if(max < arr[i]){ // 4 < 5
			max = arr[i]; // 5
		}
		if(min > arr[i]){
			min = arr[i];
		}
	}
	printf("Maximum: %d\n", max);
	printf("Minimum: %d\n", min);
	return 0;
}