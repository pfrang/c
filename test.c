#include <stdlib.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    int *ptr;
    int size = 2;
    ptr = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                ptr[0] = i;
                ptr[1] = j;
                *returnSize = size;
                return ptr;
            }
        }
    }

    // If no two numbers sum to the target, return NULL
    *returnSize = 0;
    return NULL;
}
