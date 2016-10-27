#include <alsa/asoundlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <memory>

#include "device.h"
#include "dataframe.h"
#include "psh_modem.h"


int main(int argc, char** argv) {

    std::string data = "Hello World!";

    std::shared_ptr<PSHModem> modem(new PSHModem(1000, 48000, 20));

    Device device(modem);
    Dataframe frame;
    frame.setData(data);


    if(argc > 1) {
        if(std::string(argv[1]) == "-s") {
            device.send(frame);
        } else if(std::string(argv[1]) == "-r") {
            device.receive();
        }
    }



    return 0;
}
