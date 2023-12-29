#include <stdio.h>
#include <conio.h>

int main(){
	int n,i;
	scanf("%d",&n);
	int arr[n];
	for(i=0;i<n;i++){
		scanf("%f",&arr[i]);
	}
	int clue;
	scanf("%d", &clue);
	int flag = 0;
	for(i=0;i<n;i++){
		if(arr[i] == clue){
			flag = 1; 
			break;
		}
	}
	if(flag == 1){
		printf("FOUND");
	}
	else{
		printf("NOT FOUND");
	}
	return 0;
}