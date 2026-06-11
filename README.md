# netscope

A network packet analyzer and protocol dissector built in C++.
Captures live traffic or reads pcap files and displays parsed 
protocol data in a terminal UI.

## Goals
- Learn L2/L3 networking protocols hands-on
- Practice modern C++ (C++17)
- Build toward parsing: Ethernet, ARP, IPv4, TCP/UDP, DNS, BGP, OSPF, STP, LLDP, LACP

## Dependencies
- libpcap
- ncurses
- CMake 3.16+

## Build
\```bash
mkdir build && cd build
cmake ..
make
\```

## Status
Work in progress.