#include <stdio.h>
#include <conio.h>

int main(){
	int n,i,j;
	int count;
	scanf("%d",&n);
	int arr[n];
	int freq[n];
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
		freq[i] = -1;
	}
	int visited = -1;
	for(i=0;i<n;i++){
		count = 1;
		for(j=i+1;j<n;j++){
			if(arr[i] == arr[j]){
				count++;
				freq[j] = 0;
			}
		}
		if(arr[i] != 0){
			freq[i] = count;
		}
	}
	printf("Element | Frequency \n");
	for(i=0;i<n;i++){
		if(freq[i] != 0){
			printf("%d | %d\n", arr[i], freq[i]);
		}
	}
	return 0;
}