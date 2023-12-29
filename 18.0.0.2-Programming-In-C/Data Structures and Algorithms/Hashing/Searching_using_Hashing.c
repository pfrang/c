#include <bits/stdc++.h>
using namespace std;
#define MAX 1000
bool hash_ds[MAX+1][2];

bool search(int x){
    // If the hash value is positive
    if(x >= 0){
        if(hash_ds[x][0] == 1){
            return true;
        }
        else{
            return false;
        }
    }
    // If the hash value is negative
    x = abs(x);
    if(hash_ds[x][1] == 1){
        return true;
    }
    return false;
}

void insert(int arr[], int n){
    for(int i=0;i<n;i++){
        if(arr[i] >= 0){
            hash_ds[arr[i]][0] = 1;
        }
        else{
            hash_ds[abs(arr[i])][1] = 1;
        }
    }
}

int main(){
    int arr[] = {1,2,3,4,5,6,-7,8,9,-10};
    int n = sizeof(arr)/sizeof(arr[0]);
    insert(arr,n);
    int x = 5;
    if(search(x) == true){
        printf("The value is present in Hash");
    }
    else{
        printf("The value is NOT present in Hash");
    }
    return 0;
}