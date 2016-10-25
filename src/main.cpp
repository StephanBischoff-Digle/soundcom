#include <alsa/asoundlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <memory>

#include "device.h"
#include "dataframe.h"
#include "psh_modem.h"


int main() {    
    std::string data = "Hello World!";
    
    std::shared_ptr<PSHModem> modem(new PSHModem(1000, 48000, 10));
    
    Device device(modem);
    Dataframe frame;
    frame.setData(data);
    
    device.send(frame);
    
    
    
    return 0;
}
