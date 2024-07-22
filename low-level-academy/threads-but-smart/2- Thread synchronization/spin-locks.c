#include <pthread.h>
#include <stdio.h>

#define THREAD_COUNT 10

int counter = 0;
pthread_spinlock_t counter_lock;

void *thread_target(void *vargs) {

    // THis is essentially the same code as for mutex BUT what is happening here is that instead of freezing the thread
    // (starvation) the thread is runnign in an infinite loop awaiting command
    pthread_spin_lock(&counter_lock);

    // However, mutex are almost always a better way to achieve this as it requires alot of resources for spinlocks

    for (int i = 0; i < 1000000; i++) {
        counter += 1;
    }

    pthread_spin_unlock(&counter_lock);

    printf("Counter is %d\n", counter);
}

int main(int argc, char *argv) {
    pthread_t threads[THREAD_COUNT];
    pthread_spin_init(&counter_lock, NULL);

    int i = 0;

    for (i = 0; i < THREAD_COUNT; i++) {
        if (pthread_create(&threads[i], NULL, thread_target, NULL)) {
            return -1;
        }
    }

    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_spin_destroy(&counter_lock);
    return 0;
}
