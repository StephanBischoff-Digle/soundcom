#include "device.h"

#include <cmath>
#include <iostream>
#include <fftw3.h>

bool Device::open(snd_pcm_t ** handler, accesstype actype) {
    int err;
    
    if(actype == accesstype::WRITE) {
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
    } else if(actype == accesstype::READ) {
        if((err = snd_pcm_open(handler,
                devicename_.data(),
                SND_PCM_STREAM_CAPTURE, 0)) < 0)
            return false;
        
        if((err = snd_pcm_set_params(*handler,
                SND_PCM_FORMAT_FLOAT,
                SND_PCM_ACCESS_RW_INTERLEAVED,
                1,
                samples_,
                1, 500000)) < 0)
            return false;
    } else {
        return false;
    }
    
    return true;
}

void Device::close() {
    snd_pcm_close(handler_);
}


void Device::send(const Dataframe& frame)
{
    if(!open(&handler_, accesstype::WRITE))
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


void Device::receive() {
    if(!open(&handler_, accesstype::READ))
        return;
    
    float buffer[samples_];
    long framesize = samples_/2;
    int err;
    int subsamples = 100;
    
    
    std::cout << "frame,r,i" << std::endl;
    for(auto i = 0; i < 10; i++) {
        if((err = snd_pcm_readi(handler_, buffer, framesize)) != framesize) {
            std::cout << "failed to read data" << std::endl;
        } else {
            long fftwsize = framesize / subsamples;
            fftw_complex *in, *out;
            fftw_plan p;
            
            in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * fftwsize);
            out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * fftwsize);
            p = fftw_plan_dft_1d(fftwsize, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
            
            for(auto j = 0; j < subsamples; j++) {
                for(auto k = 0; k < fftwsize; k++) {
                    in[0][k] = buffer[j * fftwsize + k];
                    in[1][k] = 0;
                }
            
                fftw_execute(p);
                for(auto k = 0; k < fftwsize; k++) {
                    std::cout << i * subsamples + j << "," <<  out[0][k] << "," << out[1][k] << std::endl;
                }
            }
            
            fftw_destroy_plan(p);
            fftw_free(in);
            fftw_free(out);
        }
    }
    
    close();
}

