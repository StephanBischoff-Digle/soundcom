#include <cmath>
#include <iostream>
#include <fftw3.h>

#include "psh_modem.h"


const std::vector<float> PSHModem::modulate(Dataframe frame) const {
    unsigned int buffersize = samples_ / baud_ * frame.getDataFrame().size();
    std::vector<float> signal;
    float phaseshift = (frame.getDataFrame()[0] ? M_PI/2 : -M_PI/4);

    int k = 0;
    for(unsigned int i = 0; i < buffersize; i++) {
        signal.push_back(sin(2 * M_PI * frequency_ / samples_ * i + phaseshift));

        if(i % (buffersize / frame.getDataFrame().size()) == 0) {
            k++;
            phaseshift = (frame.getDataFrame()[k] ? M_PI/2 : -M_PI/4);
        }
    }


    return signal;
}

const Dataframe PSHModem::demodulate(std::vector<float>& signal) const {
    unsigned int subsamples = 100;
    unsigned int fftwsize = signal.size() / subsamples;
    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * fftwsize);
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * fftwsize);
    p = fftw_plan_dft_1d(fftwsize, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    for(unsigned int j = 0; j < subsamples; j++) {
        for(unsigned int k = 0; k < fftwsize; k++) {
            in[0][k] = signal[j * fftwsize + k];
            in[1][k] = 0;
        }

        fftw_execute(p);
        for(unsigned int k = 0; k < fftwsize; k++) {
            std::cout << j << "," << out[0][k] << "," << out[1][k] << std::endl;
        }
    }

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);

    Dataframe data;
    return data;
}
