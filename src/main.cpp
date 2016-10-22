#include <alsa/asoundlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

int main() {
    snd_pcm_t * _soundDevice;
    
    snd_pcm_sframes_t frames;
    int err;
    
    if ((err = snd_pcm_open(&_soundDevice, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
            printf("Playback open error: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);
    }

    if ((err = snd_pcm_set_params(_soundDevice,
                                  SND_PCM_FORMAT_FLOAT,
                                  SND_PCM_ACCESS_RW_INTERLEAVED,
                                  1,
                                  48000,
                                  1,
                                  500000)) < 0) {   
            printf("Playback open error: %s\n", snd_strerror(err));
            exit(EXIT_FAILURE);


    }
    
    
    std::vector<bool> bitData;
    std::string data = "Hello World! Penis";
    
    std::vector<char> intermediateData(data.begin(), data.end());
    for(size_t i = 0; i < intermediateData.size(); i++) {
        char current = intermediateData[i];
        for(auto k = 0; k < 8; k++) {
            if((current >> k & 1) == 1) {
                bitData.push_back(true);
            } else {
                bitData.push_back(false);
            }
        }
    }
    
    
    for(size_t i = 1; i < bitData.size()+1; i++) {
        std::cout << bitData[i-1];
        if(i%8 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
    
    
    int baud = 10;
    int f[] = {10000, 13000, 15000, 16500};
    int framesize = 48000;
    int bitParalel = 4;
    
    unsigned long buffersize = framesize / baud * bitData.size() / bitParalel;
    
    std::cout << "buffersize: " << buffersize << std::endl;
    
    float buffer[buffersize];
    
    float phaseshift[bitParalel];
    for(auto i = 0; i < bitParalel; i++) {
        phaseshift[i] = bitData[i] ? M_PI / 2 : -M_PI / 2;
    }
    
    int k = 0;
    for(unsigned long i = 0; i < buffersize/bitParalel; i++) {
        buffer[i] = 0;
        for(auto j = 0; j < bitParalel; j++) {
            buffer[i] += sin(2 * M_PI * f[j] / framesize * i + phaseshift[j]);
        }
        
        
        if(i % (buffersize / bitData.size() / bitParalel) == 0) {
            k++;
            for(auto j = 0; j < bitParalel; j++) {
                phaseshift[j] = bitData[k+j] ? M_PI / 2 : -M_PI / 2;
            }
        }
    }
            
    for(auto i = 0; i < 1; i++) {
        frames = snd_pcm_writei(_soundDevice, buffer, buffersize);
        std::cout << frames << std::endl;
    }
    
    snd_pcm_close(_soundDevice);
    return 0;
}
