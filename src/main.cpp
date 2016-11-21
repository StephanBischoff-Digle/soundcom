#include <alsa/asoundlib.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "dataframe.h"
#include "device.h"
#include "psh_modem.h"

int main() {
  std::string data = "Hello World!";

  std::shared_ptr<PSHModem> modem(new PSHModem(2500, 48000, 10));

  Device device(modem);
  Dataframe frame;
  frame.setData(data);

  device.send(frame);

  return 0;
}
