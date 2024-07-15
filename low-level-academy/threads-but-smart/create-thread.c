
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_COUNT 10

void *thread_target(void *arg) {
    int thread_num = *((int *)arg);
    printf("I am thread number %d\n", thread_num);
    free(arg); // Free the allocated memory
    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];

    int i = 0;

    for (int i = 0; i < THREAD_COUNT; i++) {
        int *arg = malloc(sizeof(*arg)); // Allocate memory for the argument
        if (arg == NULL) {
            printf("Couldn't allocate memory for thread arg.\n");
            return 1;
        }
        *arg = i; // Set the argument value
        if (pthread_create(&threads[i], NULL, thread_target, arg)) {
            printf("Error creating thread\n");
            return 1;
        }
    }

    return 0;
}
