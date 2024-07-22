#include <pthread.h>
#include <stdio.h>

#define THREAD_COUNT 10

int counter = 0;

// Mutexes (mutual exclusions) are fundamental in ensuring that multiple threads do not execute particular sections of a
// program simultaneously. In multithreaded environments, mutexes prevent data races and ensure data integrity by
// allowing only one thread to access a code segment at a time.

pthread_mutex_t counter_lock = PTHREAD_MUTEX_INITIALIZER;

void *thread_target(void *vargs) {

    // 1 thread gets to pass but the 9 others are in starvation / wait mode
    // so we have a serious performance issue here

    // It would be as just running everything in one computation / thread so improvements should be made
    // Look at as having one ball in a jar which is taken out and put back in, but we can do better by allowing multiple
    // balls in the jar
    pthread_mutex_lock(&counter_lock);

    for (int i = 0; i < 1000000; i++) {
        counter += 1;
    }

    pthread_mutex_unlock(&counter_lock);

    printf("Counter is %d\n", counter);
}
int main(int argc, char *argv) {
    pthread_t threads[THREAD_COUNT];

    int i = 0;

    for (i = 0; i < THREAD_COUNT; i++) {
        if (pthread_create(&threads[i], NULL, thread_target, NULL)) {
            return -1;
        }
    }

    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
