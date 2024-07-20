
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_COUNT 10

typedef struct {
    int thread_num;
    char *message;
} thread_args;

void *thread_target(void *args) {
    thread_args *myargs = (thread_args *)args;
    printf("This is thread %d\n", myargs->thread_num);
    return NULL;
}

int main(int argc, char *argv) {
    pthread_t threads[THREAD_COUNT];

    int i = 0;

    thread_args arg;

    for (i = 0; i < THREAD_COUNT; i++) {

        arg.thread_num = i;

        arg.message = "Hei";

        if (pthread_create(&threads[i], NULL, thread_target, (void *)&arg) != 0) {
            printf("Error creating thread\n");
            return 1;
        }
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL); // This will prevent main thread from exiting before all threads have finished
    }

    return 0;
}
