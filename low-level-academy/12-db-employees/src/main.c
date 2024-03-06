#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "../include/common.h"
#include "../include/file.h"
#include "../include/parse.h"
// #include "common.h"
// #include "file.h"
// #include "parse.h"
//
// the program can be run with the flag -n filepath or -h
void print_usage(char *argv[]) {
  printf("Usage: %s -n -f <db file>\n", argv[0]);
  printf("\t -n - create new db file\n");
  printf("\t -f - (required) path to database file\n");
  return;
}

int main(int argc, char *argv[]) {
  char *filepath = NULL;
  bool newfile = false;
  int c;
  int dbfd = -1; // so we dont actually use it as a valid file descriptor

  struct dbheader_t *dbhdr = NULL;

  while ((c = getopt(argc, argv, "nf:")) != -1) { // if n or f is added
    switch (c) {
    case 'n':
      newfile = true;
      break;
    case 'f':
      filepath = optarg; // return value from getopt and what the command line
                         // argument was after flag
      break;
    case '?':
      printf("Unknown option -%c\n", c);
      break;
    default:
      return -1;
    }
  }

  if (filepath == NULL) {
    printf("Filepath is a required argument\n");
    print_usage(argv);
    return 0;
  }

  if (newfile) {
    dbfd = create_db_file(filepath);
    if (dbfd == STATUS_ERROR) {
      perror("Unable to create db file\n");
      return -1;
    }

    if (create_db_header(dbfd, &dbhdr) == STATUS_ERROR) {
      printf("Failed to create db header\n");
      return -1;
    }
  } else {
    dbfd = open_db_file(filepath);
    if (dbfd == STATUS_ERROR) {
      perror("Unable to open db file\n");
      return -1;
    }

    if (validate_db_header(dbfd, &dbhdr) == STATUS_ERROR) {
      printf("Failed to validate database header\n");
      return -1;
    }
  }

  printf("Newfile %d\n", newfile);
  printf("Filepath: %s\n", filepath);

  output_file(dbfd, dbhdr);

  return 0;
}
