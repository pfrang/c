#include <stdio.h>
#include <conio.h>

int binarysearch(int arr[], int n, int target){
	int low = 0;
	int high = n-1;
	while(low <= high){
		int mid = (low+high)/2;
		if(arr[mid] == target){
			return mid;
		}
		else if(arr[mid] < target){
			low = mid+1;
		}
		else{
			high = mid-1;
		}
	}
	return -1;
}

int main(){
	int n;
	scanf("%d", &n);
	int arr[n];
	for(int i=0;i<n;i++){
		scanf("%d", &arr[i]);
	}
	int target; 
	scanf("%d", &target);
	int index = binarysearch(arr, n, target);
	printf("Element is %d found at %d index", target, index);
	return 0;
}