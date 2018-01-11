#include "Socket.h"
#include <iostream>

namespace ezNetLib {
std::mutex Socket::countMutex;
unsigned int Socket::socketCount = 0;
Socket::Socket() {

  std::lock_guard<std::mutex> guard(countMutex);
  if (!socketCount) {
#ifdef _WIN32
    socketCount = 1;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
      perror("WSAStartup failed:\n");
      abort();
    }
#endif
  } else {
    ++socketCount;
  }
}

Socket::~Socket() {
  if (needClose) {
#ifdef _WIN32
    shutdown(fd, SD_BOTH);
    closesocket(fd);
#else
    shutdown(fd, SHUT_RDWR);
    close(fd);
#endif
  }
  std::lock_guard<std::mutex> guard(countMutex);
  if (socketCount) {
    --socketCount;
  }
  if (!socketCount) {
#ifdef _WIN32
    WSACleanup();
#endif
  }
}
}