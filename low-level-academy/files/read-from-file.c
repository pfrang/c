#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

struct database_header_t {
  unsigned short version;
  unsigned short employees;
  unsigned int filesize;
};
/* Created binary data my-db with echo -ne "\x01\x00\x41\x00\x08\x00\x00\x00" >
 * ./my-db.db >
 * ./my-db.db */
int main(int argc, char *argv[]) {
  struct database_header_t head = {0};

  if (argc != 2) {
    printf("Usage %s <filename>\n", argv[0]);
    return 0;
  }

  int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    perror("open");
    return -1;
  }

  if (read(fd, &head, sizeof(head)) != sizeof(head)) {
    perror("read");
    return -1;
  }

  printf("DB Version %u \n", head.version);
  printf("DB number of employees %u \n", head.employees);
  printf("DB fileize %d \n", head.filesize);

  close(fd);
  return 0;
}
