
#include <CLI/CLI.hpp>
#include <CLI/Validators.hpp>

#include "UdpGateway.hpp"

struct UdpGatewayConfig
{
    unsigned int control_port = 0;
    unsigned int data_port_a = 0;
    unsigned int data_port_b = 0;
};

int main(int const argc, char const* const argv[])
{
    CLI::App cli("UDP gateway that receives market data from a feed", "udp_md_gateway");
    cli.allow_config_extras(false);

    UdpGatewayConfig config;

    cli.set_config("-c,--config", "", "Read in a config file formatted in TOML", true)
        ->required()
        ->check(CLI::ExistingFile);

    cli.add_option("--control_port", config.control_port, "Port for TCP control socket")
        ->required()
        ->check(CLI::Range(static_cast<unsigned>(1025), static_cast<unsigned>(65'535)));

    cli.add_option("--data_port_a", config.data_port_a, "Port for UDP data socket A")
        ->required()
        ->check(CLI::Range(static_cast<unsigned>(1025), static_cast<unsigned>(65'535)));

    cli.add_option("--data_port_b", config.data_port_b, "Port for UDP data socket B")
        ->required()
        ->check(CLI::Range(static_cast<unsigned>(1025), static_cast<unsigned>(65'535)));

    CLI11_PARSE(cli, argc, argv);

    UdpGateway gateway(config.data_port_a);
    gateway.run();
    return 0;
}
