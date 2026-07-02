#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>

#define CAPACITY 128
#define DB_CAPACITY_ROW 1024

void readFile(FILE *file);
void loadFile(FILE *file);
uint32_t hash(char *key);

struct Record {
  uint32_t key_size;
  uint32_t val_size;
  char *key;
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

      printf("Query by key: \n");
      if (fgets(query, CAPACITY, stdin) == NULL) {
        free(query);
        break;
      }

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

      if (entry.key == NULL || strcmp(entry.key, query) != 0) {
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
      if (fgets(buff, CAPACITY, stdin) == NULL) {
        free(buff);
        break;
      }
      buffSize = strlen(buff);
      if (buffSize > 0 && buff[buffSize - 1] == '\n') {
        buff[--buffSize] = '\0';
      }

      if (buffSize == 0) {
        printf("Nothing was provided, try again\n");
        free(buff);
        continue;
      }

      uuid_t uuid;
      char key[UUID_STR_LEN];
      uuid_generate_random(uuid);
      uuid_unparse(uuid, key);
      uint32_t keySize = strlen(key);

      char *setBuff = malloc(sizeof(uint32_t) * 2 + keySize + buffSize);
      size_t writeOffset = 0;
      memcpy(setBuff + writeOffset, &keySize, sizeof(uint32_t));
      writeOffset += sizeof(uint32_t);
      memcpy(setBuff + writeOffset, &buffSize, sizeof(uint32_t));
      writeOffset += sizeof(uint32_t);
      memcpy(setBuff + writeOffset, key, keySize);
      writeOffset += keySize;
      memcpy(setBuff + writeOffset, buff, buffSize);

      fwrite(setBuff, sizeof(uint32_t) * 2 + keySize + buffSize, 1,
             file); // (data, byte_size, count, file)
      fflush(file);

      printf("Stored with key: %s\n", key);

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
  while (fread(&record.key_size, sizeof(uint32_t), 1, f) == 1 && db_count < DB_CAPACITY_ROW) {
    fread(&record.val_size, sizeof(uint32_t), 1, f);

    record.key = malloc(record.key_size + 1);
    fread(record.key, 1, record.key_size, f);
    record.key[record.key_size] = '\0';

    long offset = ftell(f);
    fseek(f, record.val_size, SEEK_CUR); // skip the value, we only need its location

    uint32_t index = hash(record.key);
    struct Entry *entry = malloc(sizeof(struct Entry));
    entry->key = record.key; // keydir keeps ownership of this heap string
    entry->val_size = record.val_size;
    entry->offset = offset;
    keydir[index] = *entry;
    db_count++;
    free(entry);
  };
  return;
}

void readFile(FILE *f) {

  fseek(f, 0, SEEK_SET);

  struct Record record;

  while (fread(&record.key_size, sizeof(uint32_t), 1, f) == 1) {
    fread(&record.val_size, sizeof(uint32_t), 1, f);

    record.key = malloc(record.key_size + 1);
    fread(record.key, 1, record.key_size, f);
    record.key[record.key_size] = '\0';

    record.buff = malloc(record.val_size + 1);
    fread(record.buff, 1, record.val_size, f);
    record.buff[record.val_size] = '\0';

    printf("key: %s, val_size: %u, buff: %s\n", record.key, record.val_size, record.buff);
    free(record.key);
    free(record.buff);
  }
}

uint32_t hash(char *key) {
  uint32_t h = 2166136261u; // FNV offset basis
  while (*key) {
    h ^= (unsigned char)*key++;
    h *= 16777619u; // FNV prime
  }
  return h & (DB_CAPACITY_ROW - 1);
}
