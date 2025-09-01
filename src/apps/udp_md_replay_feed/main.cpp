
#include <cstdint>

#include <CLI/CLI.hpp>
#include <CLI/Validators.hpp>

#include "UdpReplayFeed.hpp"

namespace
{
constexpr std::uint16_t min_port = 1025;
constexpr std::uint16_t max_port = 65'535;
}  // namespace

int main(int const argc, char const* argv[])
{
    CLI::App cli("Data replay feed that sends data using UDP", "udp_replay_feed");
    cli.allow_config_extras(false);

    UdpReplayFeedConfig config;

    cli.set_config("-c,--config", "", "Read in a config file formatted in TOML", true)
        ->required()
        ->check(CLI::ExistingFile);

    cli.add_option("-d,--data_file", config.data_file, "Path to .dbn data file")
        ->required()
        ->check(CLI::ExistingFile);

    cli.add_option("--control_port", config.control_port, "Port for TCP control socket")
        ->required()
        ->check(CLI::Range(min_port, max_port));

    cli.add_option("--data_port_a", config.data_port_a, "Port for UDP data socket A")
        ->required()
        ->check(CLI::Range(min_port, max_port));

    cli.add_option("--data_port_b", config.data_port_b, "Port for UDP data socket B")
        ->required()
        ->check(CLI::Range(min_port, max_port));

    CLI11_PARSE(cli, argc, argv);

    UdpReplayFeed replay_feed(config);
    replay_feed.run();
    return 0;
}
