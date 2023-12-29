#include <stdio.h>
#include <conio.h>


int main(){
	int n,i;
	scanf("%d",&n);
	int arr[n];
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	
	int s,e;
	int temp;
	for(s = 0; s<n-1; s++){ // 5,4,3,2,1 => 5
		for(e = 0; e<(n-1)-s; e++){ 
			if(arr[e] > arr[e+1]){ // 5 , 4 
				//swapping
				temp = arr[e];
				arr[e] = arr[e+1];
				arr[e+1] = temp;
			}
		}
	}
	
	for(int i=0;i<n;i++){
		printf("%d ", arr[i]);
	}
	return 0;
}