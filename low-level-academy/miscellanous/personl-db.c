#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void random_string(char *buffer);
int random_int(void);

const char NAMES[4][7] = {"Fjansk", "Espen", "Turid", "Skjan"};

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
  int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
  char buffer[50];
  sprintf(buffer, "Emplyee number\tEmployee name\tssn\n");
  write(fd, buffer, strlen(buffer));

  for (int i = 0; i < 10; i++) {
    int employee_number = random_int();
    char nameBuffer[50];
    random_string(nameBuffer);
    int ssn = random_int();
    char buffer[100] = {0};
    buffer[0] = '\0';
    sprintf(buffer, "%d\t%s\t%d\n", employee_number, nameBuffer, ssn);
    write(fd, buffer, strlen(buffer));
  }
  // Move the read position back to the start of the file
  lseek(fd, 0, SEEK_SET);

  // Read from the file and print out the contents
  char readBuffer[101]; // Buffer to hold the data read from the file
  ssize_t bytesRead;    // Number of bytes read from the file
  while ((bytesRead = read(fd, readBuffer, 100)) > 0) {
    readBuffer[bytesRead] = '\0'; // Null-terminate the string
    printf("%s", readBuffer);     // Print the string
  }

  if (bytesRead == -1) {
    perror("read");
    return -1;
  }
}

void random_string(char *buffer) {
  int random_number = rand() % 64; // Generate a random number between 0 and 63
  char *str = malloc(
      sizeof(random_number)); // allocate memory for a string of 7 characters (6
  //                           // */ digits + null terminator)
  //

  int random_num = rand() % 4;
  strcpy(buffer, NAMES[random_num]);
  /* sprintf(buffer, "%02d", random_number) */; // Convert the number to a
                                                // string, padding with zeros if
                                                // necessary
};

int random_int() {
  int random_number = rand() % 1001;
  return random_number;
}
