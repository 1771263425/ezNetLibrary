#include "Socket.h"

namespace ezNetLib {
class TcpClient : public Socket {
public:
  TcpClient();
  TcpClient(TcpClient &tcpClient) = delete;
  bool init(uint16_t port) override final;
  bool connect(sockaddr_in &addr);
  int read(char *buf, unsigned int len);
  int readLine(std::string &str);
  int write(const char *buf, unsigned int len);
  int write(std::string &str);
};
}