
#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>
#define BUFF_SIZE 1024
#define HEADER_SIZE 8

enum AckNo { SYS, SYSACK, ACK };
struct MyHeader {
  int type;
  AckNo ackno;
};

#endif
