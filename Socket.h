#ifndef EZNETLIB_SOCKET_H_
#define EZNETLIB_SOCKET_H_

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
//#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif
#include <mutex>
namespace ezNetLib {
class Socket {
public:
  Socket();
  ~Socket();
  virtual bool init(uint16_t port) = 0;

private:
  static unsigned int socketCount;
  static std::mutex countMutex;

protected:
  int fd;
  bool needClose = false;
};
}

#endif
