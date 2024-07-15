#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findMax(int arr[], int i) {
    int max = 0;

    for (int j = 0; j < i; j++) {
        if (arr[j] > max) {
            max = arr[j]; // Update the maximum value if a larger value is found
        }
    }

    return max; // Return the maximum value found
}

// Input Format
// Up to ten integers that are not the value - 1 will be read into the program.

int main() {
    srand(time(NULL)); // Seed the random number generator
    int in = 0, i = 0;
    int arr[10] = {0};

    while (in != -1 && i < 10) {
        in = rand() % 10; // Generate a random number between 0 and 9
        arr[i] = in;
        i++;
    }

    printf("The array is: ");
    for (int j = 0; j < 10; j++) {
        printf("%d ", arr[j]); // Print each element of the array
    }

    printf("\nThe maximum value in the array is: %d\n", findMax(arr, i - 1));

    return 0;
}
