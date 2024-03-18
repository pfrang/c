#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void print_stat(struct stat metaData);

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

  struct stat metaData;

  // read with man 2 stat fstat
  if (fstat(fd, &metaData) == -1) {
    perror("fstat");
    close(fd);
    return -1;
  }

  /*   you can read the file with xxd comand */

  printf("DB Version %u \n", head.version);
  printf("DB number of employees %u \n", head.employees);
  printf("DB fileize %d \n", head.filesize);
  printf("DB file size %ld\n", metaData.st_size);
  print_stat(metaData);

  if (metaData.st_size != head.filesize) {
    printf("Someting went wrong %lu from fstat is not the same as our filesize "
           "%d\n",
           metaData.st_size, head.filesize);
    close(fd);
    return -2;
  }

  close(fd);
  return 0;
}

void print_stat(struct stat metaData) {
  printf("Device ID: %ju\n", metaData.st_dev);
  printf("Inode number: %ju\n", metaData.st_ino);
  printf("Mode: %o\n", metaData.st_mode);
  printf("Number of hard links: %ju\n", metaData.st_nlink);
  printf("User ID of owner: %u\n", metaData.st_uid);
  printf("Group ID of owner: %u\n", metaData.st_gid);
  printf("Device ID (if special file): %ju\n", metaData.st_rdev);
  printf("Total size, in bytes: %jd\n", metaData.st_size);
  printf("Blocksize for filesystem I/O: %jd\n", metaData.st_blksize);
  printf("Number of 512B blocks allocated: %jd\n", metaData.st_blocks);
  // printf("Time of last access: %s", ctime(&atime));
  // printf("Time of last modification: %s", ctime(&mtime));
  // printf("Time of last status change: %s", ctime(&ctime));
}
