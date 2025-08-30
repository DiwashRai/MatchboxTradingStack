
include(FetchContent)

find_package(CLI11 CONFIG REQUIRED)
FetchContent_Declare(
		databento
		GIT_REPOSITORY https://github.com/databento/databento-cpp
		GIT_TAG HEAD
)
FetchContent_MakeAvailable(databento)

add_executable(udp_md_replay_feed
		main.cpp
		UdpReplayFeed.cpp
		UdpReplayFeed.hpp
)

target_link_libraries(udp_md_replay_feed PRIVATE
		CLI11::CLI11
		databento::databento
)
