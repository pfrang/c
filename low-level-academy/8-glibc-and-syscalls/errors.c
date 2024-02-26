#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
// We need to know what errors all external functions can return 
// read from man malloc
// For example from the open documentation
//  
//RETURN VALUE open(), openat(), and creat() return the new file descriptor, or -1 if an error occurred (in which case, errno is set appropriately). 
//        open(), openat(), and creat() can fail with the following errors:
//ERRORS
//        EACCES the requested access to the file is not allowed, or search permission is denied for one of the directories in the path prefix of pathname, or the file did not exist yet and write access to the parent
//               directory is not allowed.  (see also path_resolution(7).)
//
//        EDQUOT where o_creat is specified, the file does not exist, and the user's quota of disk blocks or inodes on the filesystem has been exhausted.
//
//        EEXIST pathname already exists and o_creat and o_excl were used.

int main() {
  int fd = open("./fhewhfew", O_RDONLY);
  // int errnum = errno;
  printf("%d\n", fd);
  if(fd == -1) {
    perror("open");// These are 2 different ways of printing the error 
    printf("Error: %s\n", strerror(errno)); // Not all libraries throws an error code which can be tracked by the global errum variable provided by errno.h
    printf("%d\n", errno);
    return -1;
  }
}
