
#ifndef HEADER_H
#define HEADER_H

#include <netinet/in.h>
#include <stdint.h>
#define BUFF_SIZE 1024
#define HEADER_SIZE 20
#define PAYLOAD_SIZE (BUFF_SIZE - HEADER_SIZE)

enum PacketType { DATA = 0, ACK = 1, RESET = 2 };
typedef struct MyHeader MyHeader;

struct MyHeader {
  uint8_t type; // PacketType
  uint32_t ackno;
  uint32_t buffLen;  // Number of valid bytes in payload
  uint32_t src_ip;   // IPv4 address in network byte order
  uint16_t src_port; // Port number in network byte order
  char buff[PAYLOAD_SIZE];
};

#endif
