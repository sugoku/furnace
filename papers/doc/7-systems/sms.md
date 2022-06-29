# Sega Master System

the predecessor to Genesis.

surely had better graphics than NES, but its sound (fairly weak, 4ch PSG with A-3 is a lowest tone) is subject of several jokes.

this console is powered by a derivative of the Texas Instruments SN76489.

the original iteration of the SN76489 used in the TI-99/4A computers was clocked much lower at 447 kHz, being able to play as low as 13.670 Hz (A -1). consequentially, pitch accuracy for higher notes is compromised.


# effects

- `20xy`: set noise mode.
  - `x` controls whether to inherit frequency from channel 3.
    - 0: use one of 3 preset frequencies (C: A-2; C#: A-3; D: A-4).
    - 1: use frequency of channel 3.
  - `y` controls whether to select noise or thin pulse.
    - 0: thin pulse.
    - 1: noise.
