#include "UdpClient.h"
#include <iostream>
namespace ezNetLib {
UdpClient::UdpClient() {}

bool UdpClient::init(uint16_t port) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = 0;
  fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (fd < 0) {
    std::cout << fd << std::endl;
    return false;
  }
  needClose = true;
  if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    return false;
  }

  return true;
}

int UdpClient::read(char *buf, unsigned int len, sockaddr_in &from) {
  int fromlen = sizeof(from);
  return recvfrom(fd, buf, len, 0, (struct sockaddr *)&from, &fromlen);
}
int UdpClient::read(char *buf, unsigned int len) {
  struct sockaddr_in from;
  return read(buf, len, from);
}

int UdpClient::write(const char *buf, unsigned int len,
                     struct sockaddr_in &to) {
  return sendto(fd, buf, len, 0, (struct sockaddr *)&to, sizeof(to));
}
}
