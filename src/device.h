#pragma once

#include <alsa/asoundlib.h>
#include <memory>
#include <string>

#include "dataframe.h"

class Device {
private:
    enum accesstype {
        READ, WRITE
    };
    snd_pcm_t * handler_;
    unsigned int frequency_;
    unsigned int samples_;
    unsigned int baud_;
    std::string devicename_;    
    
    bool open(snd_pcm_t ** handler, accesstype actype);
    void close();

public:
    Device(unsigned int frequency, unsigned int samples, unsigned int baud) :
        handler_(nullptr),
        frequency_(frequency),
        samples_(samples),
        baud_(baud),
        devicename_("default") {};
    Device(std::string devicename, unsigned int frequency, unsigned int samples, unsigned int baud) :
        handler_(nullptr),
        frequency_(frequency),
        samples_(samples),
        baud_(baud),
        devicename_(devicename) {};
    
    void send(const Dataframe& frame);
    void receive();
    
};
