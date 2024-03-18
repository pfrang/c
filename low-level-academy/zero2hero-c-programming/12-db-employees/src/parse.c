#include "../include/parse.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../include/common.h"
int update_employee(int fd, struct dbheader_t *dbhdr,
                    struct employee_t *employees) {

  if (fd < 0) {
    printf("Bad file descripton\n");
    return STATUS_ERROR;
  }

  printf("What employee do you want to update`?\n");
  printf("> ");
  char name[256];

  scanf("%s", name);

  int realcount = dbhdr->count;

  int i = 0;
  for (; i < realcount; i++) {

    if (strcmp(employees[i].name, name) == 0) {
      printf("Foudn match with %s at row %d\n", employees[i].name, i + 1);
      unsigned int hoursToUpdate = 0;

      printf("With how many hours?\n");

      scanf("%d", &hoursToUpdate);
      printf("Setting %s to %d hours\n", name, hoursToUpdate);

      employees[i].hours = hoursToUpdate;
      lseek(fd, 0, SEEK_SET);

      write(fd, dbhdr, sizeof(struct dbheader_t));

      write(fd, employees, dbhdr->count * sizeof(struct employee_t));

      return STATUS_SUCCESS;
    }
  }
  printf("Did not find any employee with that name?\n");
  return STATUS_ERROR;
}

int remove_employee(int fd, struct dbheader_t *dbhdr,
                    struct employee_t *employees, char *name) {
  if (fd < 0) {
    printf("Bad file descripton\n");
    return STATUS_ERROR;
  }

  int realcount = dbhdr->count;

  int i = 0;
  for (; i < realcount; i++) {

    if (strcmp(employees[i].name, name) == 0) {
      printf("Foudn match with %s at row %d\n", employees[i].name, i + 1);
      printf("Deleting...\n");
      for (int j = i; j < realcount - 1; j++) {
        employees[j] = employees[j + 1];
      }

      dbhdr->count--;

      dbhdr->filesize -= sizeof(struct employee_t);

      lseek(fd, 0, SEEK_SET);

      write(fd, dbhdr, sizeof(struct dbheader_t));

      write(fd, employees, dbhdr->count * sizeof(struct employee_t));

      if (ftruncate(fd, dbhdr->filesize) == -1) {
        perror("ftruncte");
        return STATUS_ERROR;
      }
      return STATUS_SUCCESS;
    }
  }

  return STATUS_ERROR;
}
// Run with ./bin/dbview -f mynewdb.db -l
// or add together ./bin/dbview -f mynewdb.db -l -a "Espen, Oppland 123, 150"
void list_employees(struct dbheader_t *dbhdr, struct employee_t *employees) {
  int i = 0;
  for (; i < dbhdr->count; i++) {
    printf("Employee %d\n", i);
    printf("\tName: %s\n", employees[i].name);
    printf("\tAddress: %s\n", employees[i].address);
    printf("\tHours: %d\n", employees[i].hours);
  }
}
int add_employee(struct dbheader_t *dbhdr, struct employee_t *employees,
                 char *addstring) {
  printf("%s\n", addstring);

  char *name = strtok(
      addstring, ","); // strtok is reading from a file splitting on provided
                       // delimiter returning pointers to each item
  // this will return the first item even though yyou pass it the entire string

  char *addr = strtok(NULL, ","); // dont provide it with a new strinig, calling
                                  // again keeps track fo hwere it was
  char *hours = strtok(NULL, ",");

  printf("%s %s %s\n", name, addr, hours);

  strncpy(employees[dbhdr->count - 1].name, name,
          sizeof(employees[dbhdr->count - 1].name));
  strncpy(employees[dbhdr->count - 1].address, addr,
          sizeof(employees[dbhdr->count - 1].address));

  employees[dbhdr->count - 1].hours = atoi(hours); // To convert string to int

  return STATUS_SUCCESS;
}

int read_employees(int fd, struct dbheader_t *dbhdr,
                   struct employee_t **employeesOut) {
  if (fd < 0) {
    printf("Got a bad FD from the user\n");
    return STATUS_ERROR;
  }

  int count = dbhdr->count;

  struct employee_t *employees = calloc(count, sizeof(struct employee_t));
  if (employees == -1) {
    printf("Malloc failed\n");
    return STATUS_ERROR;
  }

  read(fd, employees, count * sizeof(struct employee_t));

  int i = 0;

  for (; i < count; i++) {
    employees[i].hours = ntohl(employees[i].hours);
  }

  *employeesOut = employees;
  return STATUS_SUCCESS;
}

void output_file(int fd, struct dbheader_t *dbhdr,
                 struct employee_t *employees) {
  if (fd < 0) {
    printf("Got a bad FD from the user \n");
    return;
  }

  int realcount = dbhdr->count;

  dbhdr->magic =
      htonl(dbhdr->magic); // Host to network long -- to account for endianess
  dbhdr->filesize = htonl(sizeof(struct dbheader_t) +
                          (sizeof(struct employee_t) * realcount));
  dbhdr->count = htons(dbhdr->count); // Host to network short
  dbhdr->version = htons(dbhdr->version);

  lseek(fd, 0, SEEK_SET); // Sets file pointer to 0th index

  write(fd, dbhdr, sizeof(struct dbheader_t));

  int i = 0;
  for (; i < realcount; i++) {
    employees[i].hours = htonl(employees[i].hours);
    write(fd, &employees[i], sizeof(struct employee_t));
  }

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
