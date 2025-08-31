#ifndef MATCHBOXTRADINGSTACK_UDPREPLAYFEED_H
#define MATCHBOXTRADINGSTACK_UDPREPLAYFEED_H

#include <string>

struct UdpReplayFeedConfig
{
    std::string data_file;
    unsigned int control_port = 0;
    unsigned int data_port_a = 0;
    unsigned int data_port_b = 0;
};

class UdpReplayFeed
{
public:
    explicit UdpReplayFeed(UdpReplayFeedConfig config);

    void run();

private:
    void start_receive();
    void start_control_channel() const;

    UdpReplayFeedConfig m_config;
    std::string m_name;
};

#endif  // MATCHBOXTRADINGSTACK_UDPREPLAYFEED_H
