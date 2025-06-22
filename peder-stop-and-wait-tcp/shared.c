
#include <stdio.h>
#include <strings.h>

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define PORT 8080

void print_zulu_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);

  struct tm *tm_info = localtime(&tv.tv_sec);

  char buf[64];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);

  fprintf(stderr, "%s.%06ld\n", buf, tv.tv_usec);
}
