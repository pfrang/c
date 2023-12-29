#include <stdio.h>
#include <conio.h>

int main(){
	int n,i;
	scanf("%d",&n);
	int arr[n];
	for(i=1;i<n;i++){
		scanf("%d",&arr[i]);
	}
	printf("Reversing the array: ");
	for(i=n-1;i>=0;i--){
		printf("%d ",arr[i]);
	}
	return 0;
}