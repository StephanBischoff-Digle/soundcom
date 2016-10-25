#pragma once

#include <vector>
#include "dataframe.h"

class Modem {
protected:
    unsigned int frequency_;
    unsigned int samples_;
    unsigned int baud_;
    
public:
    
    Modem(unsigned int frequency, unsigned int samples, unsigned int baud) :
        frequency_(frequency),
        samples_(samples),
        baud_(baud) {};
    
    const unsigned int getFrequency() const {return frequency_;}
    const unsigned int getSamples() const {return samples_;}
    const unsigned int getBaud() const {return baud_;}
        
    virtual std::vector<float> modulate(Dataframe frame) const = 0;
    virtual Dataframe demodulate(std::vector<float> signal) const = 0;
};
