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
            samples_,
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
    
    
    unsigned long buffersize = samples_ / baud_ * frame.getDataFrame().size();
    float buffer[buffersize];
    float phaseshift = (frame.getDataFrame()[0] ? M_PI/2 : -M_PI/2);
    
    int k = 0;
    for(unsigned long i = 0; i < buffersize; i++) {
        buffer[i] = sin(2 * M_PI * frequency_ / samples_ * i + phaseshift);
        
        if(i % (buffersize / frame.getDataFrame().size()) == 0) {
            k++;
            phaseshift = (frame.getDataFrame()[k] ? M_PI/2 : -M_PI/2);
        }
    }
    
    snd_pcm_writei(handler_, buffer, buffersize);
    
    close();
}

