#pragma once

#include "modem.h"

class PSHModem : public Modem {
    std::vector<float> modulate(Dataframe frame) const override;
    Dataframe demodulate(std::vector<float> signal) const override;
    
};
