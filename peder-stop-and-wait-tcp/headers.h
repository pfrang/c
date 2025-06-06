
#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>
#define BUFF_SIZE 1024
#define HEADER_SIZE 20
#define PAYLOAD_SIZE 1004

enum PacketType { DATA, ACK, RESET };
typedef struct MyHeader MyHeader;

struct MyHeader {
  enum PacketType type;
  int ackno;
  int buffLen;
  char buff[PAYLOAD_SIZE];
};

#endif
