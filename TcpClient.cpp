#include "TcpClient.h"
#include <iostream>
namespace ezNetLib {
TcpClient::TcpClient() {}
bool TcpClient::init(uint16_t port) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = 0;
  fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
bool TcpClient::connect(sockaddr_in &addr) {
  if (::connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0) {
    return false;
  }
  return true;
}
int TcpClient::read(char *buf, unsigned int len) {
  return recv(fd, buf, len, 0);
}
int TcpClient::write(const char *buf, unsigned int len) {
  return send(fd, buf, len, 0);
}

int TcpClient::readLine(std::string &str) {
  char c;
  int res = 0;
  while (recv(fd, &c, 1, 0) == 1) {
    str.push_back(c);
    ++res;
    if (c == '\n') {
      return res;
    }
  }
  return 0;
}
int TcpClient::write(std::string &str) {
  return write(str.data(), str.length());
}
}
