#include <cmath>

#include "psh_modem.h"


std::vector<float> PSHModem::modulate(Dataframe frame) const {
    unsigned int buffersize = samples_ / baud_ * frame.getDataFrame().size();
    std::vector<float> signal;
    float phaseshift = (frame.getDataFrame()[0] ? M_PI/2 : -M_PI/4);
    
    int k = 0;
    for(unsigned int i = 0; i < buffersize; i++) {
        signal.push_back(sin(2 * M_PI * frequency_ / samples_ * i + phaseshift));
        
        if(i % (buffersize / frame.getDataFrame().size()) == 0) {
            k++;
            phaseshift = (frame.getDataFrame()[k] ? M_PI/2 : -M_PI/4);
        }
    }
    
    
    return signal;
}

Dataframe PSHModem::demodulate(std::vector<float> signal) const {
    Dataframe data;
    return data;
}
