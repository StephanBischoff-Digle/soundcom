#include <alsa/asoundlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <memory>

#include "device.h"
#include "dataframe.h"


int main() {    
    std::string data = "Hello World!";
    
    
    Device device(1000, 48000, 10);
    Dataframe frame;
    frame.setData(data);
    
    device.send(frame);
    
    
    
    return 0;
}
