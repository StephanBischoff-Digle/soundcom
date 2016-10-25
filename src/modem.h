#pragma once

#include <vector>
#include "dataframe.h"

class Modem {
public:
    
    virtual std::vector<float> modulate(Dataframe frame) const = 0;
    virtual Dataframe demodulate(std::vector<float> signal) const = 0;
};
