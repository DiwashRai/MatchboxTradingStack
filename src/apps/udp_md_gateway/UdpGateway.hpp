#ifndef MATCHBOXTRADINGSTACK_UDPGATEWAY_H
#define MATCHBOXTRADINGSTACK_UDPGATEWAY_H

class UdpGateway
{
public:
    explicit UdpGateway(int port);

    void run();

private:

    const unsigned int m_port;
};

#endif //MATCHBOXTRADINGSTACK_UDPGATEWAY_H
