#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sched.h>

// Compile program with flags -lpthread
// Run with sudo

// Setting CPU affinity restricts a thread to run on specific CPUs, optimizing performance by reducing cache misses and
// improving data locality.

void *thread_function(void *arg) {
    pthread_t tid = pthread_self(); // The thread id
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);

    printf("CPU SETSIZE: %d\n", CPU_SETSIZE);

    if (pthread_getaffinity_np(tid, sizeof(cpu_set_t), &cpuset) == 0) {
        printf("Thread %lu running on CPUs: ", (unsigned long)tid);
        for (int i = 0; i < CPU_SETSIZE; i++) {
            if (CPU_ISSET(i, &cpuset)) {
                printf("%d", i);
            }
        }
        printf("\n");
    }

    return NULL;
}

int main() {
    pthread_t thread;
    pthread_attr_t attr;
    cpu_set_t cpuset;
    struct sched_param param;

    pthread_attr_init(&attr);

    size_t stacksize = 1024 * 1024;
    // Max memory this thread will use
    pthread_attr_setstacksize(&attr, stacksize);

    pthread_attr_setschedpolicy(&attr, SCHED_RR);

    param.sched_priority = sched_get_priority_max(SCHED_RR);
    pthread_attr_setschedparam(&attr, &param);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

    CPU_ZERO(&cpuset);
    // Set that the thread is capable on running CPU 0 and 19
    CPU_SET(0, &cpuset);
    CPU_SET(19, &cpuset);
    // My CPU has 10 physical cores, allowing 2 threads per core == 20 in total, 19 is the biggest number

    pthread_attr_setaffinity_np(&attr, CPU_SETSIZE, &cpuset); // here the rules are set
    if (pthread_create(&thread, &attr, thread_function, NULL) != 0) {
        printf("Failed to create thread\n");
        return -1;
    }

    pthread_join(thread, NULL);
    pthread_attr_destroy(&attr);

    return 0;
}
