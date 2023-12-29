#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int arr[], int n){
    int i, j, min_index;
    for(i = 0; i < n-1 ; i++){
        min_index = i; // 6
        for(j = i+1; j<n; j++){
            if(arr[j] < arr[min_index]){
                min_index = j; //
            }
            if(min_index != i){
                swap(&arr[min_index], &arr[i]);
            }
        }
    }
}

int main(){
    int n; 
    scanf("%d", &n);
    int arr[n];

    // inputing the array
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }
    selectionSort(arr, n);
    // Printing the array
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    return 0;
}