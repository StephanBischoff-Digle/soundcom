#pragma once

#include "modem.h"

class PSHModem : public Modem {
public:
     PSHModem ( unsigned int frequency, unsigned int samples, unsigned int baud )
          : Modem ( frequency, samples, baud ) {};

     const std::vector<float> modulate ( Dataframe frame ) const override;
     const Dataframe demodulate ( std::vector<float> &signal ) const override;
};
