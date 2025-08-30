
#include <CLI/CLI.hpp>
#include <CLI/Validators.hpp>
#include "UdpReplayFeed.hpp"

int main(const int argc, const char* argv[])
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
        ->check(CLI::Range(1025, 65535));

    cli.add_option("--data_port_a", config.data_port_a, "Port for UDP data socket A")
        ->required()
        ->check(CLI::Range(1025, 65535));

    cli.add_option("--data_port_b", config.data_port_b, "Port for UDP data socket B")
        ->required()
        ->check(CLI::Range(1025, 65535));

    CLI11_PARSE(cli, argc, argv);

    UdpReplayFeed replay_feed(config);
    replay_feed.run();
    return 0;
}
