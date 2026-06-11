#include "pcap_reader.hpp"
#include <stdexcept>

pcap_reader::pcap_reader(const std::string& srcDevice, bool live){
    char errBuf[PCAP_ERRBUF_SIZE];
    if(live){
        int snapLen = 65535;  // max bytes to capture per packet
        int promisc = 1; // on
        int to_ms = 1000; // time out in milliseconds
        handle_ = pcap_open_live(srcDevice.c_str(), snapLen, promisc, to_ms, errBuf);
    }else{
        handle_ = pcap_open_offline(srcDevice.c_str(), errBuf);
    }
    if(!handle_) throw std::runtime_error(errBuf);
}

void pcap_reader::start(const FrameCallback&  frameCallBack){
    int err;
    pcap_pkthdr* header;
    const uint8_t* data;
    running_ = true;
    while(running_){
        err = pcap_next_ex(handle_, &header, &data);
        switch (err){
            case 0:
                // Packets are being read from a live capture and the packet buffer timeout expired
                break;
            case PCAP_ERROR_BREAK:
                // Packets are being read from a ``savefile'' and there are no more packets to read from the savefile
                return;
            case PCAP_ERROR:
                // If an error occurred while reading the packet
                throw std::runtime_error(pcap_geterr(handle_));
            case 1:{
                // The packet was read without problems,
                frame f{data, header->caplen, header->ts};
                frameCallBack(f);
                break;
            }
            default:
                break;
        }
    }
}

void pcap_reader::stop(){
    running_ = false;
}

void pcap_reader::filter(const std::string&){}

pcap_reader::~pcap_reader(){
    if(handle_) pcap_close(handle_);
}