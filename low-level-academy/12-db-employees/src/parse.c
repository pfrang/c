#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../include/common.h"
#include "../include/parse.h"

void output_file(int fd, struct dbheader_t *dbhdr) {
  if (fd < 0) {
    printf("Got a bad FD from the user \n");
    return;
  }

  dbhdr->magic =
      htonl(dbhdr->magic); // Host to network long -- to account for endianess
  dbhdr->filesize = htonl(dbhdr->filesize);
  dbhdr->count = htons(dbhdr->count); // Host to network short
  dbhdr->version = htons(dbhdr->version);

  lseek(fd, 0, SEEK_SET); // Sets file pointer to 0th index

  write(fd, dbhdr, sizeof(struct dbheader_t));

  return;
}

int validate_db_header(int fd, struct dbheader_t **headerOut) {
  if (fd < 0) {
    printf("Got a bad FD from the user \n");
    return STATUS_ERROR;
  }

  struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));

  if (header == -1) {
    printf("Malloc faild to create a db header\n");
    return STATUS_ERROR;
  }

  if (read(fd, header, sizeof(struct dbheader_t)) !=
      sizeof(struct dbheader_t)) {
    perror("read");
    free(header);
    return STATUS_ERROR;
  }

  header->version = ntohs(
      header
          ->version); // This is done to fix endianness to make it transformabl
  header->count = ntohs(header->count);
  header->magic = ntohl(header->magic);
  header->filesize = ntohl(header->filesize);

  if (header->magic != HEADER_MAGIC) {
    printf("Improper header magic \n");
    return -1;
  }

  if (header->version != 1) {
    printf("Improper header version\n");
    return -1;
  }

  struct stat dbstat = {0};
  fstat(fd,
        &dbstat); // check if header filesize number is equal to stat package

  if (header->filesize != dbstat.st_size) {
    printf("Corrupted database\n");
    return -1;
  }

  *headerOut = header;
  return STATUS_SUCCESS;
}

int create_db_header(int fd, struct dbheader_t **headerOut) {
  struct dbheader_t *header = calloc(
      1, sizeof(struct dbheader_t)); // We are able to ask the heap to give us a
                                     // memory and return that pointer
  // because we want to do stuff outside of this scope

  if (header == -1) {
    printf("Malloc failed to create db header\n");
    return STATUS_ERROR;
  }

  header->version = 0x1;
  header->count = 0;
  header->magic = HEADER_MAGIC;
  header->filesize = sizeof(struct dbheader_t);

  *headerOut = header;

  return STATUS_SUCCESS;
}
