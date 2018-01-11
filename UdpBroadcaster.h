//
// Created by Binliu on 2017/11/21.
//

#ifndef TEST2_UDPBROADCASTER_H
#define TEST2_UDPBROADCASTER_H

#include "UdpClient.h"
namespace ezNetLib {
    class UdpBroadcaster : public UdpClient {
    public:
        bool init(uint16_t port) override final{
            if(UdpClient::init(port)){
#ifdef _WIN32
            char
#else
            int
#endif
                    bOpt = true;
            int res = setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &bOpt, sizeof(bOpt));
                return true;
        } else
        return false;
        }
    };

}
#endif //TEST2_UDPBROADCASTER_H
