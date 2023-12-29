#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// 2 8 5 3 9 4
void insertionSort(int arr[], int n){
    int i, key, j;
    for(i = 1; i<n; i++){
        key = arr[i]; // 8
        j = i-1; // j = 0, arr[j] = 2
        while(j>=0 && arr[j] > key){ // arr[0] = 2 > 8
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key; // arr[0+1] = arr[1] = key = 8 => arr[1] = 8
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
    insertionSort(arr,n);
    // Printing the array
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    return 0;
}