#pragma once

#include <vector>
#include <memory>
#include "dataframe.h"

class Modem {
protected:
     std::uint_fast16_t frequency_;
     std::uint_fast16_t samples_;
     std::uint_fast16_t baud_;

public:
     Modem ( std::uint_fast16_t frequency, std::uint_fast16_t samples, std::uint_fast16_t baud )
          : frequency_ ( frequency ), samples_ ( samples ), baud_ ( baud ) {};

     const std::uint_fast16_t getFrequency() const
     {
          return frequency_;
     }
     const std::uint_fast16_t getSamples() const
     {
          return samples_;
     }
     const std::uint_fast16_t getBaud() const
     {
          return baud_;
     }

     virtual const std::vector<float> modulate ( Dataframe frame ) const = 0;
     virtual const Dataframe demodulate ( std::vector<float> &signal ) const = 0;
};
