# Soundcom

Soundcom is an application used for data transmission via sound waves.
The application is intended to be used with the Nao platform.

## ToDo Branch: `feature - send`

-   [ ] implement [QPSK](https://en.wikipedia.org/wiki/Phase-shift_keying#Quadrature_phase-shift_keying_.28QPSK.29) instead of [BPSK](https://en.wikipedia.org/wiki/Phase-shift_keying#Binary_phase-shift_keying_.28BPSK.29) as [DPSK](https://en.wikipedia.org/wiki/Phase-shift_keying#Differential_phase-shift_keying_.28DPSK.29)
-   [ ] change from hard to soft shifting
-   [ ] implement error resistant protocol

## ToDo Branch: `feature - receive`

-   [ ] extract phase shift information from the FFT
-   [ ] extract binary data from the signal
-   [ ] construct usefull data from binary
