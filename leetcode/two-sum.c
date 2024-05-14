// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to
// target.
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
// You can return the answer in any order.

#include <stdio.h>
#include <stdlib.h>
#define TARGET 6

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    printf("size %d\n", numsSize);
    int *result = malloc(2 * sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                printf("sum of %d and %d is %d\n", nums[i], nums[j], TARGET);
                result[0] = i;
                result[1] = j;
                *returnSize = 2;
                return result;
            }
        }
    }

    exit(EXIT_SUCCESS);
}

int main() {
    int input[3] = {3, 2, 3};
    int inputSize = sizeof(input) / sizeof(int);
    int returnSize;
    int *twoSumResult = twoSum(input, inputSize, TARGET, &returnSize);

    printf("Result is array [%d, %d]\n", twoSumResult[0], twoSumResult[1]);
    return 0;
}
