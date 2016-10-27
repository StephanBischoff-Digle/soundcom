#include "device.h"

#include <cmath>

bool Device::open(snd_pcm_t ** handler) {
    int err;
    if((err = snd_pcm_open(handler, 
            devicename_.data(), 
            SND_PCM_STREAM_PLAYBACK, 0)) < 0)
        return false;
    
    if((err = snd_pcm_set_params(*handler,
            SND_PCM_FORMAT_FLOAT,
            SND_PCM_ACCESS_RW_INTERLEAVED,
            1,
            modem_->getSamples(),
            1, 500000)) < 0) 
        return false;
    
    return true;
}

void Device::close() {
    snd_pcm_close(handler_);
}


void Device::send(const Dataframe& frame)
{
    if(!open(&handler_))
        return;
    
    snd_pcm_writei(handler_, modem_->modulate(frame).data(), modem_->modulate(frame).size());
    
    close();
}

