// packet capture reader header 
#pragma once
#include <cstdint>
#include <ctime> 
#include <functional>
#include <string>
#include <pcap.h>

struct frame{
    const uint8_t* bytes;
    uint32_t length;
    timeval timestamp;
};

using FrameCallback = std::function<void(const frame&)>;

class pcap_reader
{
private:
    pcap_t* handle_;
    bool running_;
public:
    pcap_reader(const std::string& srcDevice, bool live);
    
    void start(const FrameCallback&  frameCallBack);
    void stop();
    void filter(const std::string&);

    ~pcap_reader();
};