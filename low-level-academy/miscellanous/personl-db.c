#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void random_string(char *buffer);
int random_int(void);

struct database_info {
  int employee_number;
  char employee_name[50];
  int ssn;
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage %s filename: ", argv[0]);
    return -1;
  }
  int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
  char buffer[50];
  sprintf(buffer, "Emplyee number\tEmployee name\tssn\n");

  write(fd, buffer, strlen(buffer));
  for (int i = 0; i < 10000; i++) {
    int employee_number = random_int();
    char name[50];
    random_string(name);
    int ssn = random_int();
    char buffer[100];

    sprintf(buffer, "%d\t%s\t%d\n", employee_number, name, ssn);
    write(fd, buffer, sizeof(buffer));
  }
}

void random_string(char *buffer) {
  int random_number = rand() % 64; // Generate a random number between 0 and 63
  char *str = malloc(7); // Allocate memory for a string of 7 characters (6
                         // digits + null terminator)
  sprintf(buffer, "%06d", random_number); // Convert the number to a string,
                                          // padding with zeros if necessary
};

int random_int() {
  int random_number = rand() % 1001;
  return random_number;
}
