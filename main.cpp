#include "TcpClient.h"
#include "UdpClient.h"
#include <iostream>
#include <thread>
#include <vector>

using namespace ezNetLib;

void thread(int n) {
  UdpClient client;
  if (!client.init(1200 + n + 1)) {
    std::cout << "udp client init failed. " << n << std::endl;
    return;
  }
  std::shared_ptr<char> buf(new char[1024], [](char *p) { delete[] p; });
  sockaddr_in from;
  int res;
  while (1) {
    res = client.read(buf.get(), 1024, from);
    if (res > 0) {
      if (*buf == 'q') {
        std::cout << "quit thread " << n << std::endl;
        return;
      } else
        client.write(buf.get(), res, from);
    } else if (res < 0) {
      std::cout << "error occur.res=" << res << "n=" << n << std::endl;
      perror("recvfrom error:");
      return;
    }
  }
}

void test_udp() {
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; ++i)
    threads.push_back(std::thread(thread, i));
  for (std::vector<std::thread>::iterator it = threads.begin();
       it != threads.end(); ++it) {
    // it->join();
  }
}
void test_tcp() {
  TcpClient client;
  if (!client.init(1234)) {
    std::cout << "init failed tcp" << std::endl;
    return;
  }
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1234);
  addr.sin_addr.s_addr = inet_addr("172.68.1.1");
  client.connect(addr);
  std::string str;
  while (1) {
    str.clear();
    client.readLine(str);
    client.write(str);
  }
}
int main() {
  test_udp();
  test_tcp();
}