#include <stdio.h>
#include <conio.h>

int main(){
	int n,i;
	scanf("%d",&n);
	int arr[n];
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	int search;
	scanf("%d", &search);
	int cnt =  0;
	for(i=0;i<n;i++){
		if(arr[i] == search){
			cnt++;
		}
	}
	printf("Count of %d is : %d", search, cnt);
	return  0;
}