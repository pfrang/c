#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 128

void readFile(FILE *file);

struct Record {
  uint32_t val_size;
  char *buff;
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Missing file path");
    return 0;
  }

  int readRequest = 0;
  struct Record record;

  char *filePath = argv[1];
  if (argc >= 3 && strcmp(argv[2], "-r") == 0) {
    readRequest = 1;
  }

  FILE *file = fopen(filePath, readRequest ? "r" : "a");

  if (readRequest) {
    readFile(file);
  } else {
    while (1) {

      char *buff = malloc(CAPACITY);

      int buffSize;

      printf("Enter something: \n");
      fgets(buff, CAPACITY, stdin);
      buffSize = strlen(buff);
      if (buffSize > 0 && buff[buffSize - 1] == '\n') {
        buff[--buffSize] = '\0';
      }

      if (buffSize == 0) {
        printf("Nothing was provided, try again\n");
        free(buff);
        continue;
      }

      char *setBuff = malloc(sizeof(uint32_t) + buffSize);
      memcpy(setBuff, &buffSize, sizeof(int));
      // Start writing from  sizeof(int) position
      memcpy(setBuff + sizeof(int), buff, buffSize);

      fwrite(setBuff, sizeof(int) + buffSize, 1,
             file); // (data, byte_size, count, file)
      fflush(file);

      free(buff);
      free(setBuff);
    }
  }

  fclose(file);

  return 0;
}

void readFile(FILE *f) {

  fseek(f, 0, SEEK_SET);

  struct Record record;

  while (fread(&record.val_size, sizeof(uint32_t), 1, f) == 1) {
    record.buff = malloc(record.val_size + 1);
    fread(record.buff, 1, record.val_size, f);
    record.buff[record.val_size] = '\0';

    printf("val_size: %u, buff: %s\n", record.val_size, record.buff);
    free(record.buff);
  }
}
