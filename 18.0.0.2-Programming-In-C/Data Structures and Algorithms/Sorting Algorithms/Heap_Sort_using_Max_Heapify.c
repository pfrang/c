#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heap(int arr[], int N, int i){
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left<N && arr[left] > arr[largest]){
        largest = left;
    }

    if(right<N && arr[right] > arr[largest]){
        largest = right;
    }

    if(largest != i){
        swap(&arr[i], &arr[largest]);
        max_heap(arr,N,largest);
    }
}

void heap_sort(int arr[], int n){
    for(int i=n/2-1; i>=0; i--){
        max_heap(arr,n,i);
    }
    for(int i=n-1; i>=0; i--){
        swap(&arr[0], &arr[i]);
        max_heap(arr,i,0);
    }
}


int main(){
    int n;
    printf("Enter the value of the elements to be enetered: \n");
    scanf("%d", &n);
    int arr[n];
    printf("-------- BEFORE SORTING --------\n");
    printf("Enter the value of the arrays: \n");
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }
    heap_sort(arr,n);
    printf("-------- AFTER SORTING --------\n");
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    return 0;
}