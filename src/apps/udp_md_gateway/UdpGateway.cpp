
#include "UdpGateway.hpp"

#include <iostream>

#include <asio.hpp>

UdpGateway::UdpGateway(int const port) : m_port(port) {}

void UdpGateway::run()
{
    using asio::ip::udp;

    try
    {
        asio::io_context io_context;
        udp::endpoint receiver_endpoint(asio::ip::make_address("127.0.0.1"), 1234);

        udp::socket socket(io_context);
        socket.open(udp::v4());

        std::array<char, 1> send_buf = {{0}};
        socket.send_to(asio::buffer(send_buf), receiver_endpoint);

        std::array<char, 128> recv_buf;
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(asio::buffer(recv_buf), sender_endpoint);

        std::cout.write(recv_buf.data(), len);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
