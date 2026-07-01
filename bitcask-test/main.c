#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 128
#define DB_CAPACITY_ROW 1028

void readFile(FILE *file);
void loadFile(FILE *file);
uint32_t hash(char *key);

struct Record {
  uint32_t val_size;
  char *buff;
};

struct Entry {
  char *key;
  long offset;
  uint32_t val_size;
};

struct Entry keydir[DB_CAPACITY_ROW];
int db_count = 0;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Missing file path");
    return 0;
  }

  int readRequest = 0;
  int isQueryRequest = 0;
  struct Record record;

  char *filePath = argv[1];
  if (argc >= 3) {
    char *flag = argv[2];

    if (strcmp(flag, "-r") == 0) {
      readRequest = 1;
    } else if (strcmp(flag, "-q") == 0) {
      isQueryRequest = 1;
    } else {
      printf("CLI command not supported\n");
      return 0;
    }
  }

  FILE *file = fopen(filePath, (readRequest || isQueryRequest) ? "r" : "a");

  if (isQueryRequest) {
    loadFile(file);
    fseek(file, 0, SEEK_SET);

    while (1) {
      char *query = malloc(CAPACITY);

      int buffSize;

      printf("Query something: \n");
      fgets(query, CAPACITY, stdin);

      buffSize = strlen(query);

      if (buffSize > 0 && query[buffSize - 1] == '\n') {
        query[--buffSize] = '\0';
      }

      if (buffSize == 0) {
        printf("Nothing was provided, try again\n");
        free(query);
        continue;
      }

      int hashVal = hash(query);
      struct Entry entry = keydir[hashVal];

      if (entry.key == NULL) {
        printf("No record found, try again...\n");
        free(query);
        continue;
      };
      fseek(file, entry.offset, SEEK_SET);

      char *buff = malloc(entry.val_size + 1);
      fread(buff, 1, entry.val_size, file);
      buff[entry.val_size] = '\0';

      printf("Found value: %s\n", buff);
      free(buff);
    }
    return 0;
  }

  if (readRequest) {
    readFile(file);
  } else {
    while (1) {

      char *buff = malloc(CAPACITY);

      int buffSize;

      printf("Write something to DB: \n");
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

void loadFile(FILE *f) {
  fseek(f, 0, SEEK_SET);
  struct Record record;
  while (fread(&record.val_size, sizeof(uint32_t), 1, f) == 1 && db_count < DB_CAPACITY_ROW) {
    struct Entry *entry = malloc(sizeof(long) + sizeof(int) + 1);
    long offset = ftell(f);
    record.buff = malloc(record.val_size + 1);
    fread(record.buff, 1, record.val_size, f);
    record.buff[record.val_size] = '\0';
    uint32_t index = hash(record.buff);
    entry->key = "string";
    entry->val_size = record.val_size;
    entry->offset = offset;
    keydir[index] = *entry;
    db_count++;
    free(record.buff);
    free(entry);
  };
  return;
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

uint32_t hash(char *key) {
  uint32_t h = 2166136261u; // FNV offset basis
  while (*key) {
    h ^= (unsigned char)*key++;
    h *= 16777619u; // FNV prime
  }
  return h % DB_CAPACITY_ROW;
}
