#pragma once

#include <alsa/asoundlib.h>
#include <memory>
#include <string>

#include "dataframe.h"
#include "modem.h"

class Device {
private:
    snd_pcm_t * handler_;
    std::string devicename_;
    std::shared_ptr<Modem> modem_;
    
    bool open(snd_pcm_t ** handler);
    void close();

public:
    Device(std::shared_ptr<Modem> modem) :
        handler_(nullptr),
        devicename_("default"),
        modem_(move(modem)) {};
    Device(std::string devicename, std::shared_ptr<Modem> modem) :
        handler_(nullptr),
        devicename_(devicename),
        modem_(move(modem)) {};
    
    void send(const Dataframe& frame);
    
};
