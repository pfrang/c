#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

// mutex -> mutual exclusion (access)
// semaphore -> multiple access (signaling)

// Main difference between mutex and semaphore is that for a mutex the same thread that LOCKED the computation
// must be the one also unlocking. For sempaphores, any thread can lock and unlock other

// Semaphores - a concept to make your threads work together

sem_t sem;

void *signal_event() {
    printf("Doing some work...\n");
    sleep(2);
    printf("Signaling event completion!\n");
    // On posting here, the sem_wait function is being allowed to continue (the ball is put back in the jar)
    // also called signaling
    sem_post(&sem);
}

void *wait_for_event() {
    printf("Waiting for event....\n");
    // Here we are basically "locking" the jar but from a different thread
    sem_wait(&sem);
    printf("Event has been triggered!\n");
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;

    sem_init(&sem, 0, 0);

    pthread_create(&t1, NULL, wait_for_event, NULL);
    pthread_create(&t2, NULL, signal_event, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);

    return 0;
}
