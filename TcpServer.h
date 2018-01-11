#include "Socket.h"

namespace ezNetLib {
class TcpServer : public Socket {
  TcpServer(TcpClient &tcpClient) = delete;
  bool init(uint16_t port) override final;
}
}