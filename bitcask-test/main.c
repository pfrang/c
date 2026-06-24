#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 128

struct Entry {
  uint32_t val_size;
  long val_pos;
};

struct Record {
  uint32_t val_size;
  char *buff;
};

void readFile(FILE *f) {
  fseek(f, 0, SEEK_SET);

  uint32_t key_len;

  while (fread(&key_len, sizeof(uint32_t), 1, f) == 1) {
    fread(&key_len, sizeof(uint32_t), 1, f);
    long val_pos = ftell(f); // value starts here

    char *key = malloc(key_len + 1);
    fread(key, 1, key_len, f);
    key[key_len] = '\0';

    // // skip over value }

    struct Entry entry = {};
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = malloc(size + 1);
    fread(buf, 1, size, f);
    fclose(f);
  }
  // for (long i = 0; i < size; i++) {
  //   printf("%s\n", buf[i]);
  // }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Missing file path");
    return 0;
  }

  int readRequest = 0;

  char *filePath = argv[1];
  char *readMode = argv[2];
  struct Record record;

  if (strcmp(readMode, "-r") == "0") {
    readRequest = 1;
  }

  FILE *file = fopen(filePath, "a");

  if (readRequest) {
    readFile(file);
  } else {

    while (1) {

      int capacity = CAPACITY;

      char *buff = malloc(capacity);

      printf("Enter something: \n");
      fgets(buff, capacity, stdin);

      size_t buffSize = strlen(buff);

      record.val_size = buffSize;
      strcpy(record.buff, buff);
      size_t recordSize = sizeof(record);

      fwrite(&record, recordSize, 1, file); // (data, byte_size, count, file)

      free(buff);

      // readFile(file);
    }
  }
  fclose(file);

  return 0;
}
