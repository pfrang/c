#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
	int n,i;
	scanf("%d",&n);
	int arr[n];
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	int target; 
	scanf("%d", &target);
	/*
	int check = 0; //false
	for(i = 0;i<n;i++){
		if(arr[i] == target){
			check = 1;//true
			break;
		}
	}
	if(check == 1){
		printf("Found");
	}
	else{
		printf("Not found");
	}
	*/
	bool check = false;
	for(int i=0;i<n;i++){
		if(arr[i] == target){
			check = true;
			break;
		}
	}
	if(check){
		printf("Found");
	}
	else{
		printf("Not found");
	}
	return 0;
}