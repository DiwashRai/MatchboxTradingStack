
#include "UdpGateway.hpp"

#include <array>
#include <cstddef>
#include <exception>
#include <iostream>

#include <asio/buffer.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/address.hpp>
#include <asio/ip/udp.hpp>

UdpGateway::UdpGateway(int const port) : m_port(port) {}

void UdpGateway::run() const
{
    using asio::ip::udp;
    std::cout << "connecting to port: " << m_port << '\n';

    try
    {
        asio::io_context io_context;
        constexpr unsigned def_port = 1234;
        udp::endpoint const receiver_endpoint(asio::ip::make_address("127.0.0.1"), def_port);

        udp::socket socket(io_context);
        socket.open(udp::v4());

        std::array<char, 1> send_buf = {{0}};
        socket.send_to(asio::buffer(send_buf), receiver_endpoint);

        constexpr unsigned buf_size = 128;
        std::array<char, buf_size> recv_buf{};
        udp::endpoint sender_endpoint;
        size_t const len = socket.receive_from(asio::buffer(recv_buf), sender_endpoint);

        std::cout.write(recv_buf.data(), static_cast<long>(len));
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
