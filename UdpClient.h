#include "Socket.h"
#include <cstdint>
#include <string>

namespace ezNetLib {
class UdpClient : public Socket {
public:
  UdpClient();
  UdpClient(UdpClient &udpClient) = delete;
  bool init(uint16_t port) override;
  int read(char *buf, unsigned int len, struct sockaddr_in &from);
  int read(char *buf, unsigned int len);
  int write(const char *buf, unsigned int len, struct sockaddr_in &to);
};
}