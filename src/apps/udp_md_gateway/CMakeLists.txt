
message(STATUS CMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH}")
message(STATUS TOOLCHAIN="${CMAKE_TOOLCHAIN_FILE}")
message(STATUS VCPKG_INSTALLED_DIR="${VCPKG_INSTALLED_DIR}")
message(STATUS VCPKG_TARGET_TRIPLET="${VCPKG_TARGET_TRIPLET}")

find_package(CLI11 CONFIG REQUIRED)

add_executable(udp_md_gateway
        main.cpp
        UdpGateway.cpp
        UdpGateway.hpp
)

target_link_libraries(udp_md_gateway PRIVATE
        CLI11::CLI11
)
