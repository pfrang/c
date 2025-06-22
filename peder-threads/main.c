#define _GNU_SOURCE
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_function(void *arg) {
  int cpu_core = *(int *)arg;

  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(cpu_core, &cpuset);

  pthread_t thread = pthread_self();
  int rc = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
  if (rc != 0) {
    perror("pthread_setaffinity_np");
  }

  printf("Running thread on CPU %d\n", cpu_core);
  while (1)
    ;
  return NULL;
}

int main() {
  int num_cores = sysconf(_SC_NPROCESSORS_ONLN); // Get number of available cores
  printf("System has %d cores\n", num_cores);

  pthread_t threads[num_cores];
  int core_ids[num_cores];

  for (int i = 0; i < num_cores; ++i) {
    core_ids[i] = i;
    if (pthread_create(&threads[i], NULL, thread_function, &core_ids[i]) != 0) {
      perror("pthread_create");
      exit(1);
    }
  }

  for (int i = 0; i < num_cores; ++i) {
    printf("Waiting for %d core to finish\n", i);
    pthread_join(threads[i], NULL);
  }

  return 0;
}
