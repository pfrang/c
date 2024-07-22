#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

// The __thread keyword before a global variable remvoes all the work that was being done with key functionality
// One would expect when running this program that you would get an increment of 1 per thread, so 10 is logged
// You can check this by removing the __thread before and you will see the global var incremented for each thread

__thread int x_thd = 0;

void wait_for_event() {
    x_thd++;
    printf("%d\n", x_thd);
    return;
}

int main(int argc, char *argv[]) {
    pthread_t threads[10];

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, wait_for_event, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(&threads[i], NULL);
    }

    return 0;
}
