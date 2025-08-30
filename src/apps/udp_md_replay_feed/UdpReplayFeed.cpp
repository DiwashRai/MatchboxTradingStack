
#include "UdpReplayFeed.hpp"
#include "databento/record.hpp"
#include "databento/timeseries.hpp"

#include <asio/buffer.hpp>
#include <databento/dbn_file_store.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/udp.hpp>
#include <asio/ip/tcp.hpp>

#include <array>
#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

UdpReplayFeed::UdpReplayFeed(UdpReplayFeedConfig config)
    : m_config(std::move(config))
{
}

void UdpReplayFeed::run()
{
    start_control_channel();
}

void UdpReplayFeed::start_control_channel() const
{
    using asio::ip::tcp;

    try
    {
        const asio::io_context io_context;
        std::cout << m_config.control_port << '\n';
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

namespace
{
void udp_channel()
{
    using asio::ip::udp;

    asio::io_context io_context;
    constexpr unsigned int port = 1234;
    udp::socket socket(io_context, udp::endpoint(udp::v4(), port));

    try
    {
        std::string message = "testing testing 123";

        std::cout << "waiting for connection...\n";

        for (unsigned int i= 0; i < 1; ++i)
        {
            std::array<char, 1> recv_buf{};
            udp::endpoint remote_endpoint;
            socket.receive_from(asio::buffer(recv_buf), remote_endpoint);
            std::error_code ignored_error;
            socket.send_to(asio::buffer(message), remote_endpoint, 0, ignored_error);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void parse_data_file(std::string_view data_file)
{
    std::cout << data_file << '\n';
    databento::DbnFileStore store(data_file);

    long records = 0;
    auto print_action = [&](const databento::Record record) {
         const auto& mbo_msg = record.Get<databento::MboMsg>();
         std::cout << static_cast<char>(mbo_msg.action) << '\n';

         ++records;
         return databento::KeepGoing::Continue;
    };
    store.Replay(print_action);
    std::cout << records << '\n';
}

}

void UdpReplayFeed::start_receive()
{

}
