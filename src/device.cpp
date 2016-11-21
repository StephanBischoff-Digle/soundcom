#include "device.h"

#include <fftw3.h>
#include <cmath>
#include <iostream>

bool Device::open(snd_pcm_t **handler, accesstype actype) {
  int err;

  if (actype == accesstype::WRITE) {
    if ((err = snd_pcm_open(handler, devicename_.data(),
                            SND_PCM_STREAM_PLAYBACK, 0)) < 0)
      return false;

    if ((err = snd_pcm_set_params(*handler, SND_PCM_FORMAT_FLOAT,
                                  SND_PCM_ACCESS_RW_INTERLEAVED, 1,
                                  modem_->getSamples(), 1, 500000)) < 0)
      return false;
  } else if (actype == accesstype::READ) {
    if ((err = snd_pcm_open(handler, devicename_.data(), SND_PCM_STREAM_CAPTURE,
                            0)) < 0)
      return false;

    if ((err = snd_pcm_set_params(*handler, SND_PCM_FORMAT_FLOAT,
                                  SND_PCM_ACCESS_RW_INTERLEAVED, 1,
                                  modem_->getSamples(), 1, 500000)) < 0)
      return false;
  } else {
    return false;
  }

  return true;
}

void Device::close() { snd_pcm_close(handler_); }

void Device::send(const Dataframe &frame) {
  if (!open(&handler_, accesstype::WRITE)) return;

  snd_pcm_writei(handler_, modem_->modulate(frame).data(),
                 modem_->modulate(frame).size());

  close();
}

void Device::receive() {
  if (!open(&handler_, accesstype::READ)) return;

  std::uint_fast16_t framesize = modem_->getSamples() / 2;
  float buffer[framesize];

  int err;

  std::cout << "time,r,i" << std::endl;
  for (auto i = 0; i < 10; i++) {
    if ((err = snd_pcm_readi(handler_, buffer, framesize)) != framesize) {
      std::cout << "failed to read data" << std::endl;
    } else {
      std::vector<float> signalbuffer;
      signalbuffer.assign(buffer, buffer + sizeof(buffer) / sizeof(buffer[0]));

      modem_->demodulate(signalbuffer);
    }
  }

  close();
}
