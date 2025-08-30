cmake_minimum_required(VERSION 3.28)
project(MatchboxTradingStack)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_BUILD_RPATH "\$ORIGIN;\$ORIGIN/../lib")
set(CMAKE_INSTALL_RPATH "\$ORIGIN/../lib")
add_link_options(-Wl,--enable-new-dtags)

add_subdirectory(src)
