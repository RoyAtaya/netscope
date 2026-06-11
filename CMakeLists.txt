cmake_minimum_required(VERSION 3.16)
project(netscope)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(netscope src/main.cpp)
target_include_directories(netscope PRIVATE C:/npcap-sdk-1.16/Include)
target_link_directories(netscope PRIVATE C:/npcap-sdk-1.16/Lib/x64)
target_link_libraries(netscope stdc++exp wpcap ws2_32)