
#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>
#define BUFF_SIZE 1024
#define HEADER_SIZE 8
#define PAYLOAD_SIZE 1016

enum PacketType { DATA, ACK, RESET };
struct MyHeader {
  enum PacketType type;
  int ackno;
  char *buff;
  int buffLen;
};

#endif
